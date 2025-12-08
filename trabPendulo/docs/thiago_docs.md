# Documentação - Implementação Numérica (Pessoa 1)

## Método de Runge-Kutta de 4ª Ordem (RK4)

### Descrição

Este módulo implementa o método de Runge-Kutta de 4ª ordem para resolver numericamente a equação diferencial ordinária (EDO) do pêndulo simples.

### Equação Diferencial

A equação do movimento do pêndulo é:

```
d²θ/dt² = -(g/L)sin(θ)
```

Para resolver com RK4, convertemos em um sistema de duas EDOs de primeira ordem:

```
dθ/dt = ω
dω/dt = -(g/L)sin(θ)
```

Onde:
- θ = ângulo (radianos)
- ω = velocidade angular (rad/s)
- g = aceleração da gravidade (m/s²)
- L = comprimento do pêndulo (m)

### Estruturas de Dados

#### `PenduloEstado`
Representa o estado do pêndulo em um dado instante:
```c
typedef struct {
    double theta;  // ângulo (radianos)
    double omega;  // velocidade angular (rad/s)
} PenduloEstado;
```

#### `PenduloParametros`
Armazena os parâmetros físicos do sistema:
```c
typedef struct {
    double g;      // aceleração da gravidade (m/s²)
    double L;      // comprimento do pêndulo (m)
} PenduloParametros;
```

### Funções Principais

#### `pendulo_derivada()`
```c
void pendulo_derivada(double t, PenduloEstado *estado, 
                     PenduloEstado *derivada, PenduloParametros *params)
```

Calcula as derivadas do sistema:
- **Entrada**: tempo t, estado atual, parâmetros do pêndulo
- **Saída**: derivada (preenche a estrutura com dθ/dt e dω/dt)

#### `rk4_passo()`
```c
void rk4_passo(double t, PenduloEstado *estado, 
               double dt, PenduloParametros *params)
```

Executa um passo do método RK4:
- **Entrada**: tempo t, estado atual, passo de tempo dt, parâmetros
- **Saída**: atualiza o estado para o próximo instante (t + dt)

O método RK4 calcula quatro incrementos (k1, k2, k3, k4) e combina-os:
```
k1 = f(t, y)
k2 = f(t + dt/2, y + k1*dt/2)
k3 = f(t + dt/2, y + k2*dt/2)
k4 = f(t + dt, y + k3*dt)

y_new = y + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
```

#### `rk4_resolver()`
```c
void rk4_resolver(PenduloEstado *estado_inicial, double t0, double tf, 
                  int n_passos, PenduloParametros *params, 
                  PenduloEstado *solucao, double *tempo)
```

Resolve o sistema completo:
- **Entrada**: 
  - `estado_inicial`: condições iniciais
  - `t0`: tempo inicial
  - `tf`: tempo final
  - `n_passos`: número de passos de integração
  - `params`: parâmetros do pêndulo
- **Saída**:
  - `solucao`: array com estados em cada passo (tamanho n_passos+1)
  - `tempo`: array com tempos correspondentes (tamanho n_passos+1)

### Precisão e Convergência

O método RK4 é de ordem 4, o que significa:
- Erro local: O(dt⁵)
- Erro global: O(dt⁴)

**Testes de validação:**

1. **Pequenos ângulos**: Verifica convergência com a solução harmônica
2. **Conservação de energia**: Variação relativa < 10⁻⁸ para 1000 passos
3. **Grande amplitude**: Comportamento não-linear correto

### Uso

#### Exemplo básico:
```c
#include "runge_kutta.h"

// Definir parâmetros
PenduloParametros params = {.g = 9.81, .L = 1.0};

// Condições iniciais
PenduloEstado estado = {.theta = 0.5, .omega = 0.0};

// Alocar memória para solução
int n = 1000;
PenduloEstado *sol = malloc((n+1) * sizeof(PenduloEstado));
double *t = malloc((n+1) * sizeof(double));

// Resolver
rk4_resolver(&estado, 0.0, 10.0, n, &params, sol, t);

// Processar resultados...
free(sol);
free(t);
```

### Compilação

```bash
# Compilar testes
make test

# Executar testes
./test_rk4

# Compilar programa principal
make

# Executar
./pendulo
```

### Arquivos

- `src/runge_kutta.h`: Interface do módulo
- `src/runge_kutta.c`: Implementação do RK4
- `tests/test_rk4.c`: Testes de validação
- `src/main.c`: Programa principal de exemplo

### Resultados dos Testes

Exemplo de saída do `test_rk4`:

```
=== Teste 1: Pequenos ângulos ===
Período teórico: 2.0061 s
Diferença em θ: 0.000001 rad  ✓

=== Teste 2: Conservação de energia ===
Variação relativa: 1.018096e-08  ✓

=== Teste 3: Grande amplitude ===
Simulação de 10.0s com 2000 passos  ✓
```
