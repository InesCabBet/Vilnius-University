'''
  VILNIUS UNIVERSITY
  FINANCIAL TECHNOLOGY MODELS
  @author Inés Cabrera Betancor
  @date 06 OCT 2025
  @brief Program that implements RSA encryption / decryption using
  example provided in homework task 1 pdf or entering the values 
  that the user desires
'''

import math
import random

class colors:
  YELLOW = '\033[93m'
  RED = '\033[31m'
  ENDC = '\033[0m'

def showMenu():
  print("Option 1: Execute example from assignment.")
  print("Option 2: Execute own example. Introducing you own numbers")
  return input("Enter your option: ")

def areCoprime(a, b):
  return math.gcd(a, b) == 1

def isPrime(n, k=10):
  if n <= 1:
    return False
  if n <= 3:
    return True
  if n % 2 == 0:
    return False
    # descomponer n-1 como 2^r * d
  r, d = 0, n - 1
  while d % 2 == 0:
    r += 1
    d //= 2
  for _ in range(k):
    a = random.randrange(2, n - 1)
    x = pow(a, d, n)
    if x == 1 or x == n - 1:
      continue
    for _ in range(r - 1):
      x = pow(x, 2, n)
      if x == n - 1:
        break
    else:
      return False
  return True

def modinv(a, m):
  def egcd(a, b):
    if a == 0:
      return (b, 0, 1)
    else:
      g, y, x = egcd(b % a, a)
      return (g, x - (b // a) * y, y)
  g, x, _ = egcd(a, m)
  if g != 1:
    raise Exception('Modular Inverse does not exists')
  return x % m

def showInfo(p, q, e, m):
  print("\n------ INITIAL VALUES ------")
  print(f"p = {p}")
  print(f"q = {q}")
  print(f"e = {e}")
  print(f"message = {m}")

print(colors.YELLOW + "------- RSA ENCRYPTION / DECRYPTION ---------" + colors.ENDC)
option = showMenu()
if option == "1":
  p = 646253
  q = 953347 
  e = 508447791809
  m = 12345678
  showInfo(p, q, e, m)
elif option == "2":
  p = int(input("Enter value of p: "))
  q = int(input("Enter value of q: ")) 
  e = int(input("Enter value of e (public exponent): "))
  m = int(input("Enter message (integer): "))
else:
  print(colors.RED + "\nError. Invalid option. Closing program." + colors.ENDC)
  exit()

# VERIFICATIONS
if (isPrime(p) == False):
  print(colors.RED + "\nError. p value has to be prime. Closing program..." + colors.ENDC)
  exit()

if (isPrime(q) == False):
  print(colors.RED + "\nError. q value has to be prime. Closing program..." + colors.ENDC)
  exit()

if (areCoprime(p,q) == False):
  print(colors.RED + "\nError. p and q has to be coprimes. Closing program..." + colors.ENDC)
  exit()

# CALCULATIONS
n = p * q
phi_n = (p - 1) * (q - 1)

try:
  d = modinv(e, phi_n)
except Exception as ex:
  print("Error: ", ex)
  exit()

c = pow(m, e, n) # encryption
m_decrypted = pow(c, d, n) # decryption

# RESULTS
print(colors.YELLOW + "\n---- RESULTS RSA ----" + colors.ENDC)
print(f"n = {n}")
print(f"phi(n) = {phi_n}")
print(f"d = {d}")
print(f"Message encrypted (c) = {c}")
print(f"Message decrypted -> verification = {m_decrypted}")