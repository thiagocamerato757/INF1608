# Análise dos Resultados da Simulação do Pêndulo

Este documento apresenta a análise dos resultados obtidos a partir da simulação do pêndulo simples, utilizando o método de Runge-Kutta de 4ª Ordem com passo fixo e adaptativo. Os dados foram gerados pelos programas `pendulo` e `test_rk4`.

---

### Análise 1: Validade da Aproximação Linearizada

A aproximação linearizada para o período do pêndulo, $T \approx 2\pi\sqrt{L/g}$, é válida apenas para pequenos ângulos de oscilação. A análise dos resultados confirma essa teoria.

- **Confirmação do Limite de Erro:** Conforme a saída do programa, para um ângulo inicial **θ₀ ≤ 5°**, o erro absoluto entre o período calculado e o período da aproximação linearizada é de **0.000955s**, que é inferior ao critério de `0.001s`. A análise automatizada do script também confirma que 5° é o ângulo máximo para manter o erro abaixo desse limiar.

- **Crescimento do Erro com o Ângulo:** O erro da aproximação linearizada cresce de forma não linear à medida que o ângulo inicial aumenta. Isso ocorre porque o termo `sin(θ)` se afasta cada vez mais de `θ` em ângulos maiores.

A tabela abaixo demonstra a relação entre o ângulo inicial, o período calculado pelo método adaptativo (considerado o mais preciso), e o erro percentual em relação ao período linearizado constante de `2.006067 s`.

| Ângulo Inicial (θ₀) | Período Calculado (s) | Erro da Aproximação Linearizada (%) |
|:-------------------:|:---------------------:|:-----------------------------------:|
| 5.0°                | 2.007003              | 0.0476%                             |
| 10.0°               | 2.009917              | 0.1904%                             |
| 30.0°               | 2.041003              | 1.7111%                             |
| 45.0°               | 2.086253              | 3.8437%                             |
| 60.0°               | 2.152874              | 6.8192%                             |
| 90.0°               | 2.367843              | 15.2787%                            |
| 120.0°              | 2.754091              | 27.1604%                            |
| 150.0°              | 3.535110              | 43.2529%                            |

---

### Análise 2: Eficiência dos Métodos

A eficiência de um método numérico pode ser medida pela sua capacidade de atingir uma determinada precisão com o menor custo computacional (número de passos ou tempo de CPU).

- **Comparação de Passos vs. Precisão:** Os resultados mostram que, para um mesmo ângulo inicial, os métodos de passo fixo (`h = 0.01`, `0.001`, `0.0001`) produzem períodos quase idênticos. Isso sugere que `h = 0.01` já oferece uma precisão suficiente e diminuir o passo não melhora significativamente o resultado, apenas aumenta o custo computacional.

- **Superioridade do Passo Adaptativo:** O método de passo adaptativo (com tolerância ε=1e-5) alcança uma precisão comparável ou superior à do método de passo fixo mais fino (`h = 0.0001`), mas com uma fração do número de passos.

A tabela abaixo compara o número de passos para o método de passo fixo mais preciso e o método adaptativo para diferentes ângulos.

| Ângulo Inicial (θ₀) | Passos (h=0.0001) | Passos (Adaptativo) | Redução de Passos |
|:-------------------:|:-----------------:|:-------------------:|:-----------------:|
| 45.0°               | 300910            | 473                 | ~636x             |
| 90.0°               | 300910            | 501                 | ~600x             |
| 120.0°              | 300910            | 548                 | ~550x             |

O método adaptativo é drasticamente mais eficiente, ajustando o tamanho do passo para ser maior em trechos de baixa variação da solução e menor em trechos de alta variação, otimizando o uso de recursos computacionais.

---

### Análise 3: Dependência do Período com o Ângulo Inicial (θ₀)

Diferente do modelo linearizado, o período de um pêndulo real depende de sua amplitude (ângulo inicial).

- **Aumento do Período com θ₀:** Os dados experimentais mostram claramente que o período de oscilação (T) aumenta à medida que o ângulo inicial (θ₀) aumenta. Isso evidencia a natureza não linear do sistema. Para θ₀ = 5°, o período é de `2.007s`, enquanto para θ₀ = 150°, ele atinge `3.535s`, um aumento de mais de 75%.

A relação pode ser visualizada na seguinte tabela:

| Ângulo Inicial (θ₀) | Período (T) Calculado (s) | Período Teórico Linearizado (s) |
|:-------------------:|:-------------------------:|:-------------------------------:|
| 5.0°                | 2.007003                  | 2.006067                        |
| 10.0°               | 2.009917                  | 2.006067                        |
| 30.0°               | 2.041003                  | 2.006067                        |
| 45.0°               | 2.086253                  | 2.006067                        |
| 90.0°               | 2.367843                  | 2.006067                        |
| 150.0°              | 3.535110                  | 2.006067                        |

Enquanto o modelo linearizado prevê um período constante, o modelo não linear, resolvido numericamente, captura o comportamento físico real com alta fidelidade.

---

### Análise 4: Execução em Tempo Real

Uma simulação é considerada "em tempo real" se o tempo de computação for menor que o tempo físico que ela simula.

- **Confirmação do Tempo Real:** Todos os métodos testados rodam significativamente mais rápido que o tempo real. Por exemplo, para simular um período completo (cerca de 2.4 segundos de tempo físico para θ₀ = 90°), o método mais lento (`h = 0.0001`) levou apenas `13.70 ms` (ou `0.0137 s`). O método adaptativo foi ainda mais rápido, levando `0.11 ms`.

- **Fator de Aceleração:** O fator de aceleração (`Tempo Físico Simulado / Tempo de CPU`) quantifica o quão mais rápido a simulação é.

Vamos calcular o fator de aceleração para o caso de **θ₀ = 90°**, onde o período simulado foi de `2.368s`.

| Método              | Tempo de CPU (s) | Fator de Aceleração (aprox.) |
|:--------------------|:----------------:|:----------------------------:|
| h = 0.01            | 0.00016          | 14,800x                      |
| h = 0.001           | 0.00154          | 1,537x                       |
| h = 0.0001          | 0.01370          | 173x                         |
| Adaptativo (ε=1e-5) | 0.00011          | **21,527x**                  |

**Conclusão:** Todos os métodos são extremamente rápidos, com o método adaptativo sendo o mais eficiente, rodando mais de 20.000 vezes mais rápido que o fenômeno físico real. Isso demonstra a viabilidade de usar tais simulações para análises rápidas e interativas.
