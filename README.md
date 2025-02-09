# Newton-Raphson x RSA

<img align="right" width="128px" src="./.media/math.png">

![Version Badge](https://img.shields.io/badge/status-in%20development-red)

This repository contains the implementations presented in the study article `Numerical Methods in Cryptography: Newton-Raphson vs. RSA`. The study aims to evaluate the efficiency of the Newton-Raphson (NR) method in solving the modular inverse problem, comparing it to well-established approaches such as the Extended Euclidean Algorithm (EEA) and Fermat-Euler Theorem (FET). To achieve this, benchmarks were performed using a (highly) simplified RSA implementation as a pratical example. The article was developed as the final project for the Numerical Calculus course at UTFPR-TD.

## Development status

<!---
Possible status:
:white_check_mark: Done
:black_square_button: In progress
:white_square_button: Planned
--->

| Feature                  | Status                             | Description |
|:-------------------------|:-----------------------------------|:------------|
| Software designing       | :white_check_mark: Done            | Decide which languages to use and how to implement the algorithms |
| Simplified RSA           | :black_square_button: In progress  | Implement the 5 steps of RSA, except for the 'd' parameter |
| Extended Euclidean (EEA) | :white_check_mark: Done            | Implement the Extended Euclidean Algorithm |
| Fermat-Euler Theorem (FET) | :black_square_button: In progress | Implement the Fermat-Euler Theorem |
| Newton-Raphson (NR)      | :black_square_button: In progress  | Implement the Newton-Raphson method |

## Instructions

To compile the code and run the benchmarks, use the `build.sh` script:

```bash
$ ./build.sh
```

## License

This project is licensed under the [MIT License](https://opensource.org/licence/MIT). Fell free to use, modify, and distribute the code as needed. See the [LICENSE](LICENSE) file for more information.
