# Newton-Raphson x Euclides Estendido

<img align="right" width="128px" src="./.media/math.png">

![Version Badge](https://img.shields.io/badge/status-in%20development-red)

Esse repositório contém as implementações abordadas no artigo de estudo `Criptografia: Newton-Raphson e Euclides Estendido, Um Estudo Comparativo`. O objetivo do estudo é comparar a eficácia do Algoritmo de Euclides Estendido (AEE) com o método de Newton-Rasphson (NR). Para tal, realizamos benchmarks utilizando uma implementação (muito) simplificada do RSA como exemplo prático. O artigo foi desenvolvido como trabalho de conclusão da disciplina de Cálculo Numérico na UTFPR-TD.

## Status de desenvolvimento

<!---
Possible status:
:white_check_mark: Done
:black_square_button: In progress
:white_square_button: Planned
--->

| Feature                  | Status                             | Description |
|:-------------------------|:-----------------------------------|:------------|
| Software designing       | :black_square_button: In progress  | Decidir quais linguagens utilizar, e como implementar o RSA, AEE e NR |
| Simplified RSA           | :white_square_button: Planned      | Implementar as 5 etapas do RSA com exceção do parâmetro 'd' (que é calculado via AEE e/ou NR) |
| Euclides estendido (AEE) | :white_square_button: Planned      | Implementar o Algoritmo de Euclides estendido |
| Newton-Raphson (NR)      | :white_square_button: Planned      | Implementar o método de Newton-Rasphson |

## Instruções

Para compilar os códigos e executar os benchmarks, use o script `build.sh`:

```bash
$ ./build.sh
```

## License

Esse repositório e seus códigos estão sobre a [LICENÇA MIT](http://opensource.org/license/MIT). Sinta-se à vontade para usar, modificar e distribuir o código conforme necessário. Consulte o arquivo [LICENSE](LICENSE) para mais informações.
