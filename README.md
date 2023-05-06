# Compressor/Decompressor de arquivos de texto

O programa utiliza do método [LZ78](https://pt.wikipedia.org/wiki/LZ78) para comprimir e descomprimir arquivos. O dicionário usado no método foi implementado por meio de uma [trie (árvore de prefixos)](https://pt.wikipedia.org/wiki/Trie).

# Como usar

Para utilizar o programa, primeiro é necessário compilá-lo. Para isso, basta invocar o comando `make` no diretórion onde o programa se encontra (por padrão, é o mesmo diretório desta documentação). Em seguida, podemos utilizar o programa.

## Compressão

Para comprimir um arquivo, usamos o seguinte comando:
`lz78-compress -c <caminho-do-arquivo-para-comprimir> [-o <caminho-do-arquivo-comprimido>]`

A segunda opção (`-o <comprimido>`) é opcional. Por padrão, o arquivo de saída será criado no mesmo diretório do arquivo de entrada e receberá o nome da entrada com a extensão `.lz78`.

## Descompressão

Para descomprimir um arquivo, usamos o seguinte comando:
`lz78-compress -x <caminho-do-arquivo-para-descomprimir> [-o <caminho-do-arquivo-descomprimido>]`

A segunda opção (`-o <comprimido>`) é opcional. Por padrão, o arquivo de saída será criado no mesmo diretório do arquivo de entrada e receberá o nome da entrada com a extensão `.txt`.

# Taxa de Compressão

Foi inserido no diretório raiz do repositório um programa escrito em python chamado `test.py` e uma pasta chamada test, contendo 10 livros no formato `.txt`. Pode-se executar o script `test.py` para se obter a taxa de compressão para cada um dos livros na pasta test. Segue a taxa de cada arquivo:

| Livro                                                      | Taxa de compressão |
| ---------------------------------------------------------- | ------------------ |
| constituicao1988.txt                                       | 45.35 %            |
| dom_casmurro.txt                                           | 27.64 %            |
| Fiodor_Dostoievski_os_Irmãos_Karamazov.txt                 | 39.04 %            |
| Isaac_Asimov_Fundação.txt                                  | 29.12 %            |
| J.\_R.\_R.\_Tolkien_as_Duas_Torres.txt                     | 35.29 %            |
| J.\_R.\_R.\_Tolkien_a_Sociedade_do_Anel.txt                | 37.58 %            |
| J.\_R.\_R.\_Tolkien_o_Retorno_do_Rei.txt                   | 36.58 %            |
| Júlio_Verne_Viagem_Ao_Centro_da_Terra.txt                  | 26.50 %            |
| Ludwig\*Von_Mises_Ação_Humana\*\-_um_Tratado_de_Economia.txt | 45.60 %            |
| os_lusiadas.txt                                            | 24.44 %            |

Obs.: Os valores da tabela a foram truncados com a precisão de duas casas decimais.

# Implementação

O programa foi implementado integralmente em C++ compilado usando o compilador g++ do [GCC](https://gcc.gnu.org/) (com exceção do script de testes `test.py`) sem o uso de bibliotecas externas. O desenvolvimento se deu em um subsistema linux para windows ([wsl2](https://learn.microsoft.com/en-us/windows/wsl/)) utilizando a distro [Ubuntu](https://ubuntu.com/wsl).

## Estruturas de Dados e Algoritmos

Como dito anteriormente, o algoritmo usado foi o [LZ78](https://pt.wikipedia.org/wiki/LZ78), utilizando uma [árvore trie compacta (árvore de prefixos compacta)](https://pt.wikipedia.org/wiki/Trie) para implemetar o dicionário. A codificação de um texto produz um vetor de tuplas, onde o primeiro elemento é um número inteiro positivo e o segundo é um caractere (índice, caractere).

### Otimização

Se armazados de forma convencional, cada tupla presente no vetor seria transcrita para um arquivo de texto na forma:

> `<índice>,<caractere>`\
> `<índice>,<caractere>`\
> `<índice>,<caractere>`\
> ...

Essa representação usaria um byte para armazenar a vírgula (ou o outro caractere escolhido) que separa os elementos, um byte para armazenar a quebra de linha (ou o outro caractere escolhido) que separa as tuplas e um byte para armazenar o caractere, além de um byte para cada algarismo do índice (representado em base decimal), o que pode se tornar muito ineficiente para grandes textos, uma vez que os índices tendem a se tornar números cada vez maiores com o crescimento do texto.

Podemos obter uma maior economia de espaço se fixarmos o tamanho de cada tupla, utilizando um número fixo de bytes para o índice, mais um byte para o caractere. Dessa forma nos livramos da necessidade de armazenar os caracteres para separar os elementos e as tuplas. Dessa forma, foram utilizados 3 bytes para representar o índice, e mais um para representar o caractere. Assim, toda tupla ocupa exatamente 4 bytes. Ao escolher representar cada índice com 3 bytes, limitamos o dicionário ao indice máximo de $(2^8)^3=2^{24}= 16.777.216$. Essa limitação não é um problema, pois mesmo os maiores livros (por exemplo a Bíblia Sagrada ou A Revolta de Atlas (Ayn Rand)) possuem cerca de 3 a 4 milhões de caracteres, e considerando que, a medida que mais texto é inserido, maior será a probabilidade de um prefixo se repetir. Dessa forma, é impossível, na prática, superar esse limite.

---
