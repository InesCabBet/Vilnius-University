import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
from sklearn.metrics import accuracy_score

# --- 1. Carga y Preprocesamiento de Datos ---
# Cargar el dataset.
df = pd.read_csv("cross sales bank.csv")

# Eliminar la columna 'duration' (Duración del último contacto), según lo solicitado.
df = df.drop('duration', axis=1)

# Codificar la variable objetivo 'deposit': 'yes' -> 1, 'no' -> 0
df['deposit'] = df['deposit'].map({'yes': 1, 'no': 0})

# Identificar columnas categóricas (incluyendo 'day' como nominal)
categorical_cols = df.select_dtypes(include=['object']).columns.tolist()
categorical_cols.append('day')

# Aplicar One-Hot Encoding a las variables categóricas
df_encoded = pd.get_dummies(df, columns=categorical_cols, drop_first=True)

# Separar características (X) y objetivo (y)
X = df_encoded.drop('deposit', axis=1)
y = df_encoded['deposit']

# Dividir los datos en conjuntos de entrenamiento (70%) y prueba (30%)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42, stratify=y)

# Identificar columnas numéricas para el escalado
numerical_cols = ['age', 'balance', 'campaign', 'pdays', 'previous']
results = {}

# --- 2. Función de Evaluación y Entrenamiento ---
def evaluate_model(model, model_name, is_scaling_required=False):
    """Entrena y evalúa un modelo, guardando el Error de Prueba."""
    
    X_train_final = X_train.copy()
    X_test_final = X_test.copy()
    
    if is_scaling_required:
        # Escalar datos numéricos SÓLO si es requerido (para LR y SVC)
        scaler = StandardScaler()
        scaler.fit(X_train_final[numerical_cols])
        
        X_train_final[numerical_cols] = scaler.transform(X_train_final[numerical_cols])
        X_test_final[numerical_cols] = scaler.transform(X_test_final[numerical_cols])
        
    # Entrenar el modelo
    model.fit(X_train_final, y_train)
    
    # Predecir en el conjunto de prueba
    y_pred = model.predict(X_test_final)
        
    # Calcular el error de prueba (1 - Precisión)
    accuracy = accuracy_score(y_test, y_pred)
    test_error = 1 - accuracy
    
    results[model_name] = test_error
    print(f"{model_name} Test Error: {test_error:.4f}")

# --- 3. Entrenamiento y Evaluación de Modelos ---

print("--- Models evaluation ---")

# 3.1 Logistic Regression (Requiere escalado)
lr = LogisticRegression(solver='liblinear', random_state=42, max_iter=1000)
evaluate_model(lr, 'Logistic Regression', is_scaling_required=True)

# 3.2 Support Vector Classifier (SVC) (Requiere escalado)
svc = SVC(kernel='linear', C=0.1, random_state=42)
evaluate_model(svc, 'SVC (Linear Kernel)', is_scaling_required=True)

# 3.3 Random Forest (No requiere escalado)
rf = RandomForestClassifier(n_estimators=100, random_state=42, n_jobs=-1)
evaluate_model(rf, 'Random Forest', is_scaling_required=False)

# 3.4 Gradient Boosting (Sustituto de XGBoost) (No requiere escalado)
# Usamos GradientBoostingClassifier de sklearn como sustituto de XGBoost
gbc = GradientBoostingClassifier(n_estimators=100, random_state=42)
evaluate_model(gbc, 'Gradient Boosting (XGB Proxy)', is_scaling_required=False)


# --- 4. Comparación de Resultados ---

print("\n--- Final Results & Comparation ---")
results_df = pd.DataFrame(results.items(), columns=['Model', 'Test Error'])
results_df['Test Error (%)'] = (results_df['Test Error'] * 100).round(2).astype(str) + '%'
results_df = results_df.sort_values(by='Test Error')

print(results_df)

print(f"\nThe best model is: **{results_df.iloc[0]['Model']}** with a test error of **{results_df.iloc[0]['Test Error (%)']}**.")