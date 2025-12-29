"""
@author Inés Cabrera Betancor
@date 26 DEC 2025

NYSE Time Series Analysis - Lab 10.9.6 Modified
Based on Introduction to Statistical Learning with Python (ISLP)
Chapter 10: Deep Learning - Recurrent Neural Networks

Tasks:
a) Refit flattened ANN with 12-level month factor and weekday dummy
b) Fit linear AR model using flattened ANN and compare with LinearRegression
c) Adjust RNN to include weekday dummy

Requirements: torch, pandas, numpy, sklearn, ISLP, pytorch_lightning
"""

import numpy as np
import pandas as pd
import torch
from torch import nn
from torch.utils.data import TensorDataset
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score
from pytorch_lightning import Trainer, seed_everything
from pytorch_lightning.loggers import CSVLogger
from torchmetrics import R2Score, MeanSquaredError

try:
    from ISLP import load_data
    from ISLP.torch import SimpleDataModule, SimpleModule, ErrorTracker
    print("✓ ISLP imported successfully")
except ImportError:
    print("ERROR: ISLP not installed. Run: pip install ISLP")
    exit(1)

# Set seed
seed_everything(42, workers=True)
torch.use_deterministic_algorithms(True, warn_only=True)

print("=" * 80)
print("LOADING NYSE DATA")
print("=" * 80)

# Load NYSE data
NYSE = load_data('NYSE')
print(f"Shape: {NYSE.shape}")
print(f"Columns: {list(NYSE.columns)}")
print(f"\nFirst rows:\n{NYSE.head()}")

# Reset index to access date
NYSE = NYSE.reset_index()
NYSE['date'] = pd.to_datetime(NYSE['date'])
NYSE['month'] = NYSE['date'].dt.month
NYSE['day_num'] = NYSE['date'].dt.dayofweek

# Create dummy variables for weekday
day_dummies = pd.get_dummies(NYSE['day_of_week'], prefix='day', drop_first=True)
NYSE = pd.concat([NYSE, day_dummies], axis=1)
NYSE = NYSE.drop('day_of_week', axis=1)  # ← ELIMINA LA COLUMNA STRING

print(f"\nAfter adding dummies: {NYSE.shape}")
print(f"Columns now: {list(NYSE.columns)}")

# Create lagged features
print("\n" + "=" * 80)
print("CREATING LAGGED FEATURES")
print("=" * 80)

n_lags = 5
for lag in range(1, n_lags + 1):
    NYSE[f'log_volume_lag{lag}'] = NYSE['log_volume'].shift(lag)
    NYSE[f'DJ_return_lag{lag}'] = NYSE['DJ_return'].shift(lag)

# Remove rows with NaN (from lagging)
NYSE = NYSE.dropna()
print(f"Shape after lagging: {NYSE.shape}")

# Define features and target
lag_cols = [col for col in NYSE.columns if 'lag' in col]
day_cols = [col for col in NYSE.columns if col.startswith('day_')]
feature_cols = lag_cols + day_cols

print(f"\nLag columns: {lag_cols}")
print(f"Day columns: {day_cols}")
print(f"Total features: {len(feature_cols)}")

X = NYSE[feature_cols].values.astype(np.float32)
y = NYSE['log_volume'].values.astype(np.float32)
months = NYSE['month'].values

print(f"\nX shape: {X.shape}")
print(f"y shape: {y.shape}")

# Split train/test (80/20)
split_idx = int(0.8 * len(X))
X_train, X_test = X[:split_idx], X[split_idx:]
y_train, y_test = y[:split_idx], y[split_idx:]
months_train, months_test = months[:split_idx], months[split_idx:]

print(f"Train: {X_train.shape}, Test: {X_test.shape}")

# ============================================================================
# TASK A: ANN with Month Factor
# ============================================================================
print("\n" + "=" * 80)
print("TASK A: Flattened ANN with Month Factor")
print("=" * 80)

# Create month dummies
month_dummies_train = pd.get_dummies(months_train, prefix='month')
month_dummies_test = pd.get_dummies(months_test, prefix='month')

# Align columns
for i in range(1, 13):
    col = f'month_{i}'
    if col not in month_dummies_train:
        month_dummies_train[col] = 0
    if col not in month_dummies_test:
        month_dummies_test[col] = 0

month_cols = sorted([c for c in month_dummies_train.columns])
month_dummies_train = month_dummies_train[month_cols].values
month_dummies_test = month_dummies_test[month_cols].values

X_train_month = np.concatenate([X_train, month_dummies_train], axis=1).astype(np.float32)
X_test_month = np.concatenate([X_test, month_dummies_test], axis=1).astype(np.float32)

print(f"Features WITHOUT month: {X_train.shape[1]}")
print(f"Features WITH month: {X_train_month.shape[1]}")

# Model
class FlattenedANN(nn.Module):
    def __init__(self, input_size):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(input_size, 64),
            nn.ReLU(),
            nn.Dropout(0.3),
            nn.Linear(64, 32),
            nn.ReLU(),
            nn.Dropout(0.2),
            nn.Linear(32, 1)
        )
    
    def forward(self, x):
        return torch.flatten(self.net(x))

# Prepare data
train_ds = TensorDataset(torch.tensor(X_train_month), torch.tensor(y_train))
test_ds = TensorDataset(torch.tensor(X_test_month), torch.tensor(y_test))

dm = SimpleDataModule(train_ds, test_ds, batch_size=32, num_workers=0, validation=0.2)

model = FlattenedANN(X_train_month.shape[1])
module = SimpleModule.regression(model, metrics={'r2': R2Score(), 'mse': MeanSquaredError()})

logger = CSVLogger('logs', name='A_ANN_Month')
trainer = Trainer(max_epochs=30, logger=logger, enable_progress_bar=True, 
                 callbacks=[ErrorTracker()], deterministic=True)

print("\nTraining ANN with month factor...")
trainer.fit(module, datamodule=dm)

results_a = trainer.test(module, datamodule=dm)
print(f"\n{'='*80}")
print(f"TASK A RESULTS:")
print(f"{'='*80}")
print(f"Test R²:  {results_a[0]['test_r2']:.4f}")
print(f"Test MSE: {results_a[0]['test_mse']:.4f}")

# ============================================================================
# TASK B: Linear AR (ANN vs sklearn)
# ============================================================================
print("\n" + "=" * 80)
print("TASK B: Linear AR Model Comparison")
print("=" * 80)

# B1: ANN with no hidden layers
class LinearANN(nn.Module):
    def __init__(self, input_size):
        super().__init__()
        self.linear = nn.Linear(input_size, 1)
    
    def forward(self, x):
        return torch.flatten(self.linear(x))

train_ds_b = TensorDataset(torch.tensor(X_train), torch.tensor(y_train))
test_ds_b = TensorDataset(torch.tensor(X_test), torch.tensor(y_test))
dm_b = SimpleDataModule(train_ds_b, test_ds_b, batch_size=32, num_workers=0, validation=0.2)

model_b = LinearANN(X_train.shape[1])
module_b = SimpleModule.regression(model_b, metrics={'r2': R2Score(), 'mse': MeanSquaredError()})

logger_b = CSVLogger('logs', name='B_LinearANN')
trainer_b = Trainer(max_epochs=30, logger=logger_b, enable_progress_bar=True,
                   callbacks=[ErrorTracker()], deterministic=True)

print("Training Linear ANN...")
trainer_b.fit(module_b, datamodule=dm_b)
results_b_ann = trainer_b.test(module_b, datamodule=dm_b)

# B2: sklearn LinearRegression
print("\nTraining sklearn LinearRegression...")
lr = LinearRegression()
lr.fit(X_train, y_train)
y_pred = lr.predict(X_test)
r2_sklearn = r2_score(y_test, y_pred)
mse_sklearn = np.mean((y_test - y_pred) ** 2)

print(f"\n{'='*80}")
print(f"TASK B RESULTS:")
print(f"{'='*80}")
print(f"Linear ANN (PyTorch):")
print(f"  R²:  {results_b_ann[0]['test_r2']:.4f}")
print(f"  MSE: {results_b_ann[0]['test_mse']:.4f}")
print(f"\nLinearRegression (sklearn):")
print(f"  R²:  {r2_sklearn:.4f}")
print(f"  MSE: {mse_sklearn:.4f}")
print(f"\nDifference in R²: {abs(results_b_ann[0]['test_r2'] - r2_sklearn):.6f}")

# ============================================================================
# TASK C: RNN with Weekday
# ============================================================================
print("\n" + "=" * 80)
print("TASK C: RNN with Weekday Dummy")
print("=" * 80)

# Create sequences
seq_len = 5

def create_sequences(X, y, seq_len):
    Xs, ys = [], []
    for i in range(len(X) - seq_len):
        Xs.append(X[i:i+seq_len])
        ys.append(y[i+seq_len])
    return np.array(Xs, dtype=np.float32), np.array(ys, dtype=np.float32)

X_seq_train, y_seq_train = create_sequences(X_train, y_train, seq_len)
X_seq_test, y_seq_test = create_sequences(X_test, y_test, seq_len)

print(f"Sequence shape - Train: {X_seq_train.shape}, Test: {X_seq_test.shape}")

class RNN_Model(nn.Module):
    def __init__(self, input_size, hidden_size=50, num_layers=2):
        super().__init__()
        self.rnn = nn.RNN(input_size, hidden_size, num_layers, 
                         batch_first=True, dropout=0.3 if num_layers > 1 else 0)
        self.fc = nn.Linear(hidden_size, 1)
    
    def forward(self, x):
        out, _ = self.rnn(x)
        out = self.fc(out[:, -1, :])
        return torch.flatten(out)

train_ds_c = TensorDataset(torch.tensor(X_seq_train), torch.tensor(y_seq_train))
test_ds_c = TensorDataset(torch.tensor(X_seq_test), torch.tensor(y_seq_test))
dm_c = SimpleDataModule(train_ds_c, test_ds_c, batch_size=32, num_workers=0, validation=0.2)

model_c = RNN_Model(X_train.shape[1], hidden_size=50, num_layers=2)
module_c = SimpleModule.regression(model_c, metrics={'r2': R2Score(), 'mse': MeanSquaredError()})

logger_c = CSVLogger('logs', name='C_RNN')
trainer_c = Trainer(max_epochs=30, logger=logger_c, enable_progress_bar=True,
                   callbacks=[ErrorTracker()], deterministic=True)

print("Training RNN...")
trainer_c.fit(module_c, datamodule=dm_c)
results_c = trainer_c.test(module_c, datamodule=dm_c)

print(f"\n{'='*80}")
print(f"TASK C RESULTS:")
print(f"{'='*80}")
print(f"Test R²:  {results_c[0]['test_r2']:.4f}")
print(f"Test MSE: {results_c[0]['test_mse']:.4f}")

# ============================================================================
# SUMMARY
# ============================================================================
print("\n" + "=" * 80)
print("FINAL SUMMARY - ALL TASKS")
print("=" * 80)
print(f"\nTask A (ANN + Month Factor):")
print(f"  R² = {results_a[0]['test_r2']:.4f}")
print(f"\nTask B (Linear Models):")
print(f"  Linear ANN:  R² = {results_b_ann[0]['test_r2']:.4f}")
print(f"  sklearn LR:  R² = {r2_sklearn:.4f}")
print(f"  Difference:  {abs(results_b_ann[0]['test_r2'] - r2_sklearn):.6f}")
print(f"\nTask C (RNN with Weekday):")
print(f"  R² = {results_c[0]['test_r2']:.4f}")

print("\n" + "=" * 80)
print("✓ ANALYSIS COMPLETE!")
print("=" * 80)
print("\nLogs saved in ./logs/ directory")
print("Check the academic paper for detailed commentary on results.")