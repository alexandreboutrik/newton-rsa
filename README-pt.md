# Newton-Raphson x RSA

<img align="right" width="128px" src="./.media/math.png">

![Version Badge](https://img.shields.io/badge/status-in%20development-red)

Esse repositório contém as implementações abordadas no artigo de estudo `Métodos Numéricos na Criptografia: Newton-Raphson vs. RSA`. O objetivo do estudo é comparar a eficácia do método de Newton-Raphson (NR) na resolução do problema do inverso modular, comparando-o com abordagens bem estabelecidas, como o Algoritmo de Euclides Estendido (EEA) e o Teorema de Fermat-Euler (FET). Para tal, realizamos benchmarks utilizando uma implementação (muito) simplificada do RSA como exemplo prático. O artigo foi desenvolvido como trabalho de conclusão da disciplina de Cálculo Numérico na UTFPR-TD.

## Status de desenvolvimento

<!---
Possible status:
:black_check_mark: Done
:black_square_button: In progress
:white_square_button: Planned
--->

| -                        | Status                             | Description |
|:-------------------------|:-----------------------------------|:------------|
| Software designing       | :white_check_mark: Done            | Decidir quais linguagens utilizar, e como implementar os algoritmos |
| RSA simplificado         | :black_square_button: In progess   | Implementar as 5 etapas do RSA com exceção do parâmetro 'd' |
| Euclides estendido (EEA) | :white_check_mark: Done            | Implementar o Algoritmo de Euclides estendido |
| Fermat-Euler (FET)       | :black_square_button: In progress  | Implementar o Teorema de Fermat-Euler |
| Newton-Raphson (NR)      | :black_square_button: In progress  | Implementar o método de Newton-Rasphson |
| Benchmark                | :white_square_button: Planned      | Realizar os testes de benchmark |
| Escrita do artigo        | :black_square_button: In progress  | Terminar de escrever o artigo |
| Publicação do artigo     | :white_square_button: Planned      | Publicar o artigo em alguma Revista |

## Instruções

Para compilar os códigos e executar os benchmarks, use o script `build.sh`:

```bash
$ ./build.sh
```

## License

Esse repositório e seus códigos estão sobre a [LICENÇA MIT](http://opensource.org/license/MIT). Sinta-se à vontade para usar, modificar e distribuir o código conforme necessário. Consulte o arquivo [LICENSE](LICENSE) para mais informações.
