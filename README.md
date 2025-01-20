# Newton-Raphson x Euclides Estendido

<img align="right" width="128px" src="./.media/math.png">

![Version Badge](https://img.shields.io/badge/status-in%20development-red)

Esse repositório contém as implementações discutidas no artigo de estudo `Criptografia: Newton-Raphson e Euclides Estendido, Um Estudo Comparativo`. O objetivo do estudo é comparar o Algoritmo de Euclides Estendido com o método de Newton-Rasphson. Para tal, realizamos benchmarks utilizando uma implementação (muito) simplificada do RSA como exemplo prático.

## Status de desenvolvimento

<!---
:white_check_mark: Done
:black_square_button: In progress
:white_square_button: Planned
--->

| Feature                  | Status                             | Description |
|:-------------------------|:-----------------------------------|:------------|
| Design                   | :black_square_button: In progress  | Decidir quais linguagens utilizar para implementar os algoritmos |
| RSA                      | :white_square_button: Planned      | Implementar os 4 passo-a-passos do RSA com exceção do parâmetro 'd' |
| Euclides                 | :white_square_button: Planned      | Implementar o Algoritmo de Euclides estendido |
| Newton-Raphson           | :white_square_button: Planned      | Implementar o método de Newton-Rasphson |

## Instruções

Os benchmarks são executados em um ambiente Docker. Para compilar os códigos e executar os benchmarks, use o script `build.sh`:

```bash
$ ./build.sh
```

## License

Esse repositório e seus códigos estão sobre a [LICENÇA MIT](http://opensource.org/license/MIT). Sinta-se à vontade para usar, modificar e distribuir o código conforme necessário. Consulte o arquivo [LICENSE](LICENSE) para mais informações.
