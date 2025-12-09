# Documentação do Projeto - Simulação de Pêndulo

## Status da Implementação

### ✅ IMPLEMENTADO (Thiago)

#### 1. Método de Runge-Kutta de 4ª Ordem

**Equação Diferencial NÃO LINEAR implementada:**
```
θ̈ + (g/L)sin(θ) = 0
```

Convertida para sistema de primeira ordem:
```
dθ/dt = ω
dω/dt = -(g/L)sin(θ)  ← SEM LINEARIZAÇÃO!
```

**Funcionalidades:**
- ✅ RK4 com passo constante (h = 0.01, 0.001, 0.0001)
- ✅ RK4 com passo adaptativo (ε = 10⁻⁵)
- ✅ Estratégia de dobrar o passo para estimar erro
- ✅ Solução analítica linearizada (apenas para comparação)

#### 2. Cálculo do Período

**Método implementado:**
- ✅ Detecção de mudança de sinal da velocidade angular (ω)
- ✅ Interpolação linear conforme fórmula do PDF:
  ```
  T = 2[t₁ + |v₁|/(|v₁|+|v₂|)(t₂-t₁)]
  ```
- ✅ Uso de múltiplas inversões (10 períodos) para maior precisão

#### 3. Experimentos Automatizados

**Programa principal (`./pendulo`):**
- ✅ Testa 8 ângulos diferentes: 5°, 10°, 30°, 45°, 60°, 90°, 120°, 150°
- ✅ Compara 5 métodos para cada ângulo:
  - Solução analítica linearizada
  - RK4 com h = 0.01
  - RK4 com h = 0.001
  - RK4 com h = 0.0001
  - RK4 adaptativo (ε = 10⁻⁵)
- ✅ Calcula automaticamente:
  - Período para cada método
  - Número de passos utilizados
  - Tempo de CPU (ms)
  - Erro relativo da aproximação linearizada

#### 4. Análises Solicitadas no PDF

**Implementado:**
- ✅ Quadro comparativo de período e número de passos
- ✅ Cálculo do ângulo máximo para erro < 0.001s → **Resultado: θ₀,max = 5.0°**
- ✅ Tempo de execução para 10 períodos
- ✅ Verificação de execução em tempo real → **Sim, > 1000x mais rápido**

#### 5. Dados Gerados

**Arquivos criados automaticamente:**
```
data/
├── comparacao_theta10.txt   # θ₀ = 10°
├── comparacao_theta45.txt   # θ₀ = 45°
└── comparacao_theta90.txt   # θ₀ = 90°
```

**Formato dos arquivos:**
```
# Comparação: Solução Numérica vs Solução Analítica
# θ₀ = 0.7854 rad (45.0 graus)
# t(s)  theta_num(rad)  theta_anal(rad)  diferenca(rad)
0.000000  0.785398  0.785398  0.000000
0.000100  0.785398  0.785398  0.000000
...
```

---

## ⏳ PENDENTE

### 1. Plotagem dos Resultados

**Gráficos a serem gerados:**

#### Gráfico 1: θ × t (um ciclo completo)
Para cada ângulo inicial (10°, 45°, 90°):
- Plotar solução numérica (linha azul contínua)
- Plotar solução analítica linearizada (linha vermelha tracejada)
- Título: "Comparação de Soluções - θ₀ = XX°"
- Eixo X: Tempo (s)
- Eixo Y: θ (graus ou radianos)

#### Gráfico 2: Diferença entre soluções
Para cada ângulo inicial:
- Plotar |θ_numérico - θ_analítico| vs tempo
- Mostra onde a linearização falha
- Eixo X: Tempo (s)
- Eixo Y: Diferença (rad ou graus)

**Arquivos de entrada disponíveis:**
- `data/comparacao_theta10.txt`
- `data/comparacao_theta45.txt`
- `data/comparacao_theta90.txt`

**Sugestão de implementação (Python):**
```python
import numpy as np
import matplotlib.pyplot as plt

# Ler dados
data = np.loadtxt('data/comparacao_theta45.txt')
t = data[:, 0]
theta_num = data[:, 1]
theta_anal = data[:, 2]

# Plotar
plt.figure(figsize=(10, 6))
plt.plot(t, np.degrees(theta_num), 'b-', label='Numérico (RK4)')
plt.plot(t, np.degrees(theta_anal), 'r--', label='Analítico (linearizado)')
plt.xlabel('Tempo (s)')
plt.ylabel('θ (graus)')
plt.title('Comparação de Soluções - θ₀ = 45°')
plt.grid(True)
plt.legend()
plt.savefig('plots/comparacao_theta45.png')
```

### 2. Análise dos Resultados

**Análises a serem feitas:**

#### Análise 1: Validade da Aproximação Linearizada
- Confirmar que para θ₀ ≤ 5°, erro < 0.001s
- Mostrar como o erro cresce com o ângulo inicial
- Tabela ou gráfico de erro vs θ₀

#### Análise 2: Eficiência dos Métodos
- Comparar número de passos vs precisão
- Mostrar que passo adaptativo é ~600x mais eficiente
- Gráfico: passos vs h (para métodos de passo constante)

#### Análise 3: Dependência do Período com θ₀
- Gráfico: T(θ₀) vs θ₀
- Mostrar que T aumenta com θ₀ (não linearidade)
- Comparar com T_teórico constante

#### Análise 4: Tempo Real
- Confirmar que todos os métodos executam em tempo real
- Calcular fator de aceleração para cada método
- Tabela comparativa

### 3. Relatório Final
---

## Estruturas de Dados

### `PenduloEstado`
Representa o estado do pêndulo em um dado instante:
```c
typedef struct {
    double theta;  // ângulo (radianos)
    double omega;  // velocidade angular (rad/s)
} PenduloEstado;
```

### `PenduloParametros`
Armazena os parâmetros físicos do sistema:
```c
typedef struct {
    double g;      // aceleração da gravidade (m/s²)
    double L;      // comprimento do pêndulo (m)
} PenduloParametros;
```

---

## Funções Implementadas

### `pendulo_derivada()`
```c
void pendulo_derivada(double t, PenduloEstado *estado,
                     PenduloEstado *derivada, PenduloParametros *params)
```
Calcula as derivadas do sistema (dθ/dt = ω, dω/dt = -(g/L)sin(θ))

### `rk4_passo()`
```c
void rk4_passo(double t, PenduloEstado *estado,
               double dt, PenduloParametros *params)
```
Executa um passo do método RK4 clássico

### `rk4_passo_com_erro()`
```c
void rk4_passo_com_erro(double t, PenduloEstado *estado,
                        double dt, PenduloParametros *params, double *erro)
```
Passo RK4 com estimativa de erro (dobrar o passo)

### `rk4_resolver()`
```c
void rk4_resolver(PenduloEstado *estado_inicial, double t0, double tf,
                  int n_passos, PenduloParametros *params,
                  PenduloEstado *solucao, double *tempo)
```
Resolve com passo constante

### `rk4_adaptativo()`
```c
int rk4_adaptativo(PenduloEstado *estado_inicial, double t0, double tf,
                   double epsilon, PenduloParametros *params,
                   PenduloEstado **solucao, double **tempo, int max_passos)
```
Resolve com passo adaptativo (ε = 10⁻⁵)

### `calcular_periodo()`
```c
double calcular_periodo(PenduloEstado *solucao, double *tempo,
                       int n_pontos, int n_inversoes)
```
Calcula o período usando interpolação linear

### `solucao_analitica()`
```c
double solucao_analitica(double t, double theta0, PenduloParametros *params)
```
Retorna θ(t) = θ₀cos(√(g/L)t) - solução linearizada

---

## Como Usar

### Compilar
```bash
make clean
make
```

### Executar experimentos completos
```bash
./pendulo
```

### Executar testes de validação
```bash
make test
./test_rk4
```

### Executar tudo (script completo)
```bash
./executar_tudo.sh
```

---

## Exemplo de Saída

```
========================================
Experimento: θ₀ = 45.0 graus (0.7854 rad)
========================================

Período teórico (linearizado): 2.006067 s

Método              Período (s)    Passos          Tempo CPU (ms)
--------------------------------------------------------------------------------
Analítico           2.006067        N/A             N/A
h = 0.01            2.086256        3009            0.14
h = 0.001           2.086256        30091           1.29
h = 0.0001          2.086256        300910          12.63
Adaptativo (ε=1e-5) 2.086253        473             0.10

Erro da aproximação linearizada: 0.080189 (3.8437%)
```

---

## Arquivos do Projeto

```
trabPendulo/
├── src/
│   ├── main.c              # Experimentos automatizados ✅
│   ├── runge_kutta.c       # Implementação RK4 ✅
│   └── runge_kutta.h       # Interface ✅
├── tests/
│   └── test_rk4.c          # Testes de validação ✅
├── data/
│   └── comparacao_*.txt    # Dados gerados ✅
├── plots/                  # Para gráficos ⏳
├── docs/
│   ├── thiago_docs.md      # Este arquivo ✅
│   └── tomás_docs.md       # Relatório da dupla ⏳
├── Makefile                # Compilação ✅
├── executar_tudo.sh        # Script completo ✅
├── exemplos.sh             # Exemplos de uso ✅
├── pendulo.pdf             # Enunciado original
└── relatório.pdf           # Relatório Final ⏳
```

**Legenda:**
- ✅ = Implementado
- ⏳ = Pendente

---

## Referências

- Enunciado: `pendulo.pdf`
- Press, W. H. et al. "Numerical Recipes in C"
- Butcher, J. C. "Numerical Methods for Ordinary Differential Equations"
