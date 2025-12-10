# Relatório do Trabalho: Simulação do Pêndulo Simples

**Nomes:** Thiago Camerato e Tomás Lenzi
**Matrículas:** matrícula e 2220711

---

## Introdução

Este trabalho aborda o estudo do movimento do pêndulo simples, um problema clássico da física que demonstra conceitos importantes sobre oscilações e equações diferenciais. O objetivo principal do projeto é utilizar o método numérico de Runge-Kutta de 4ª ordem (RK4) para resolver a equação diferencial não linear que descreve o movimento do pêndulo.

A solução numérica obtida é então comparada com a solução analítica simplificada, que é válida apenas para pequenas amplitudes de oscilação. Para otimizar a precisão e a eficiência computacional, o método RK4 foi implementado tanto com passo constante quanto com uma estratégia de passo adaptativo, que ajusta o tamanho do passo para manter o erro local sob um limite pré-definido de ε = 10⁻⁵.

O relatório apresenta o desenvolvimento do modelo matemático e dos métodos numéricos empregados, seguido por uma análise detalhada dos resultados computacionais, comparando a precisão, o custo computacional e a validade das diferentes abordagens para vários ângulos iniciais.

---

## Desenvolvimento

O movimento de um pêndulo simples, de comprimento `L` sob a ação da gravidade `g`, é descrito pela seguinte equação diferencial ordinária (EDO) de segunda ordem:

$$ \frac{d^2\theta}{dt^2} + \frac{g}{L}\sin(\theta) = 0 $$

Onde `θ` é o ângulo em relação à vertical. Esta é uma EDO não linear devido ao termo `sin(θ)`. Para resolvê-la numericamente, primeiro a convertemos em um sistema de duas EDOs de primeira ordem, definindo `ω = dθ/dt` (velocidade angular):

1.  `dθ/dt = ω`
2.  `dω/dt = - (g/L) sin(θ)`

Este sistema foi resolvido utilizando o **método de Runge-Kutta de 4ª Ordem**. A implementação foi feita em linguagem C, contemplando duas estratégias principais de integração:

- **Passo Fixo:** O método RK4 foi aplicado com três passos constantes diferentes (`h = 0.01s`, `h = 0.001s` e `h = 0.0001s`) para avaliar o impacto do tamanho do passo na precisão e no custo computacional.
- **Passo Adaptativo:** Foi implementada uma estratégia de passo adaptativo para otimizar a simulação. A cada passo, o erro local é estimado comparando o resultado de um passo `h` com dois passos `h/2`. Se o erro for maior que a tolerância `ε = 10⁻⁵`, o passo é reduzido; se for muito menor, o passo é aumentado para o passo seguinte. Esta abordagem visa garantir a precisão desejada com o menor número de cálculos possível.

Para fins de comparação, também foi utilizada a **solução analítica aproximada**, derivada da linearização `sin(θ) ≈ θ` para pequenos ângulos. Esta aproximação transforma a EDO em um oscilador harmônico simples com solução `θ(t) = θ₀ cos(√(g/L)t)`, cujo período é constante e dado por `T ≈ 2π√(L/g)`.

O período `T` do ciclo foi calculado numericamente monitorando a mudança de sinal da velocidade angular `ω`, utilizando interpolação linear para estimar o instante exato da inversão e, consequentemente, o meio período. Para maior precisão, o tempo de 10 períodos foi medido e então dividido por 10.

---

## Resultados e Análise

Esta seção apresenta os resultados obtidos através dos experimentos computacionais, focando na comparação entre a solução numérica e a analítica, na eficiência dos métodos e na dependência do período com a amplitude.

### Validade da Aproximação Linearizada

Os experimentos confirmam que a solução analítica simplificada só é precisa para ângulos iniciais pequenos. O erro da aproximação cresce rapidamente com o aumento do ângulo inicial (`θ₀`).

- **Limite de Erro:** Nossos testes indicam que para um ângulo inicial **θ₀ ≤ 5°**, o erro absoluto no período é inferior a `0.001s`, satisfazendo o critério do enunciado.
- **Análise Gráfica:** Os gráficos de comparação ilustram visualmente essa divergência. Para `θ₀ = 10°`, as curvas numérica e analítica são quase indistinguíveis. No entanto, para `θ₀ = 45°` e, de forma mais acentuada, para `θ₀ = 90°`, a solução analítica se afasta significativamente da solução numérica, que representa o comportamento físico mais preciso.

![Comparação de Soluções para θ₀ = 10°](../plots/comparacao_theta10.png)
_Figura 1: Comparação entre a solução numérica (azul) e a analítica (vermelho tracejado) para um ângulo inicial de 10°. A sobreposição quase perfeita indica a alta precisão da aproximação linear para pequenos ângulos._

![Comparação de Soluções para θ₀ = 45°](../plots/comparacao_theta45.png)
_Figura 2: Comparação para um ângulo inicial de 45°. A divergência entre as soluções começa a se tornar visível, com a solução numérica apresentando um período ligeiramente maior._

![Comparação de Soluções para θ₀ = 90°](../plots/comparacao_theta90.png)
_Figura 3: Comparação para um ângulo inicial de 90°. A diferença é acentuada. O período da solução numérica é visivelmente maior, demonstrando que a aproximação linearizada não é mais adequada para grandes amplitudes._

Os gráficos de diferença (`|θ_num - θ_anal|`) quantificam o erro ao longo do tempo.

![Diferença entre Soluções para θ₀ = 10°](../plots/diferenca_theta10.png)
_Figura 4: Erro absoluto entre as soluções para θ₀ = 10°. O erro permanece pequeno, na ordem de 10⁻³ radianos._

![Diferença entre Soluções para θ₀ = 45°](../plots/diferenca_theta45.png)
_Figura 5: Erro absoluto para θ₀ = 45°. O erro cresce de forma secular, atingindo valores significativos ao longo do ciclo._

![Diferença entre Soluções para θ₀ = 90°](../plots/diferenca_theta90.png)
_Figura 6: Erro absoluto para θ₀ = 90°. O erro é substancial, ultrapassando 0.2 radianos e evidenciando a falha da aproximação linear._

### Eficiência dos Métodos e Análise do Período

A análise do período e do número de passos revela a superioridade do método adaptativo.

| Ângulo Inicial (θ₀) | Período (Adaptativo) | Passos (h=0.0001) | Passos (Adaptativo) | Redução de Passos |
| :-----------------: | :------------------: | :---------------: | :-----------------: | :---------------: |
|        45.0°        |      2.086253 s      |      300910       |         473         |       ~636x       |
|        90.0°        |      2.367843 s      |      300910       |         501         |       ~600x       |
|       120.0°        |      2.754091 s      |      300910       |         548         |       ~550x       |

Como a tabela mostra, o **método de passo adaptativo** alcança precisão comparável à do passo fixo mais fino (`h=0.0001`), mas com uma redução drástica no número de passos (e, portanto, no custo computacional), sendo cerca de **600 vezes mais eficiente**.

Além disso, ao contrário do modelo linearizado que prevê um período constante (`T ≈ 2.006s`), os resultados numéricos demonstram que o **período do pêndulo aumenta com a amplitude inicial**, um fenômeno característico de osciladores não lineares. Para `θ₀ = 5°`, o período foi de `2.007s`, enquanto para `θ₀ = 150°`, o período aumentou para `3.535s`.

### Análise de Tempo de Execução

Todas as estratégias de simulação executaram em tempo significativamente menor que o tempo físico simulado. Para simular 10 períodos com `θ₀ = 90°` (aproximadamente 24 segundos de tempo físico), o método de passo adaptativo levou cerca de `0.11 ms`, resultando em um fator de aceleração superior a **20.000x**. Isso significa que a simulação é mais de 20.000 vezes mais rápida que o evento real, confirmando que o sistema não apenas executa em tempo real, como o faz com extrema eficiência.

---

## Conclusão

Este trabalho realizou com sucesso a simulação do pêndulo simples utilizando o método de Runge-Kutta de 4ª ordem. A implementação de um método de passo adaptativo provou ser crucial, oferecendo um equilíbrio excelente entre precisão e eficiência computacional, sendo centenas de vezes mais rápido que a abordagem de passo fixo para a mesma precisão.

As análises confirmaram computacionalmente que a aproximação linearizada para o movimento do pêndulo só é válida para pequenas amplitudes (até 5° para um erro de período inferior a 0.001s) e que o período de oscilação real aumenta com a amplitude inicial. Finalmente, demonstrou-se que as simulações são executadas com altíssima performance, milhares de vezes mais rápido que o tempo real, validando a eficácia dos métodos numéricos empregados para a análise de sistemas dinâmicos.

---

## Referências

[1] Press, W. H., Teukolsky, S. A., Vetterling, W. T., & Flannery, B. P. (1992). _Numerical Recipes in C: The Art of Scientific Computing_. 2nd ed. Cambridge University Press.

[2] Butcher, J. C. (2008). _Numerical Methods for Ordinary Differential Equations_. 2nd ed. John Wiley & Sons.

[3] INF1608 (2024), "Enunciado do Trabalho do Pêndulo", `pendulo.pdf`.
