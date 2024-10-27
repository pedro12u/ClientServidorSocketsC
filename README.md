# Cliente-Servidor Sockets em C com TCP e UDP

Este projeto é uma biblioteca em C que permite a comunicação entre um cliente e um servidor para transferir arquivos, utilizando os protocolos TCP e UDP.

## Objetivo do Experimento

- O objetivo aqui é entender como funciona a comunicação entre cliente e servidor, explorando as diferenças entre os protocolos TCP e UDP:
  - **TCP**: Protocolo mais confiável, que garante que os dados cheguem na ordem e sem erros.
  - **UDP**: Protocolo rápido e simples, que não verifica se os dados foram entregues corretamente ou em ordem.
- Além disso, queremos comparar como cada um deles se comporta em termos de velocidade e confiabilidade na transferência de arquivos.

## Estrutura do Projeto

```
ClienteServidorSocketsC/
├── TCP_Server.c         # Código do servidor TCP
├── TCP_Client.c         # Código do cliente TCP
├── UDP_Server.c         # Código do servidor UDP
├── UDP_Client.c         # Código do cliente UDP
├── file_to_send.txt     # Arquivo teste (1KB)
└── README.md            # Instruções e notas do experimento
```

## Requisitos

- **Ambiente de desenvolvimento C** MinGW(Para Windows).
- **Arquivo de teste** (`file_to_send.txt`): Um arquivo de texto pequeno(1kb) que vai ser enviado do client para o servidor.

## Como Compilar

Abaixo estão os comandos para compilar cada componente do projeto. Eles devem ser executados no diretório ClienteServidorSocketsC.

### Compilar o Servidor TCP

```bash
gcc TCP_Server.c -o TCP_Server -lws2_32  # Para Windows
```

### Compilar o Cliente TCP

```bash
gcc TCP_Client.c -o TCP_Client -lws2_32  # Para Windows
```

### Compilar o Servidor UDP

```bash
gcc UDP_Server.c -o UDP_Server -lws2_32  # Para Windows
```

### Compilar o Cliente UDP

```bash
gcc UDP_Client.c -o UDP_Client -lws2_32  # Para Windows
```

## Execução do Experimento

### 1. Experimento com TCP

#### Iniciar o Servidor TCP

Abra um terminal e inicie o servidor TCP:

```bash
./TCP_Server
```

O servidor vai mostrar: `Servidor TCP aguardando conexões...`.

#### Iniciar o Cliente TCP

Abra um segundo terminal e inicie o cliente TCP:

```bash
./TCP_Client
```

O cliente vai mostrar: `Conectado ao servidor. Enviando arquivo...` e depois `Arquivo enviado ao servidor...`.

#### Verificar Recebimento

O servidor deve mostrar: `Arquivo recebido e salvo como 'received_tcp.txt'`.
No mesmo diretório do servidor, você encontrará o arquivo `received_tcp.txt` com o conteúdo do arquivo transferido.

### 2. Experimento com UDP

#### Iniciar o Servidor UDP

No terminal, execute o servidor UDP:

```bash
./UDP_Server
```

O servidor vai mostrar: `Servidor UDP aguardando pacotes...`.

#### Iniciar o Cliente UDP

Em um segundo terminal, execute o cliente UDP:

```bash
./UDP_Client
```

O cliente exibe: `Conectado ao servidor UDP. Enviando arquivo...` e `Arquivo enviado ao servidor...`.

#### Verificar Recebimento

O servidor deve mostrar: `Fim da transmissão recebido.` e `Arquivo recebido e salvo como 'received_udp.txt'`.
Verifique o arquivo `received_udp.txt` no diretório do servidor.

## Análise e Comparação

### Confiabilidade

- **TCP** é confiável: garante que os dados cheguem completos e na ordem correta, mesmo que leve um pouco mais de tempo.
- **UDP** não tem as mesmas garantias: é mais rápido, mas alguns dados podem se perder ou chegar fora de ordem, especialmente em redes mais instáveis.

### Tempo de Transmissão

- **UDP** é geralmente mais rápido, pois não precisa verificar se cada parte dos dados foi entregue corretamente.
- **TCP** pode ser mais lento por ter esse controle, mas é muito útil quando você precisa que todos os dados cheguem certinho e na ordem certa.
- Para observar essa diferença de velocidade, você pode cronometrar a transferência dos arquivos ou fazer os testes em uma rede mais lenta.

## Notas

- **Ambientes Diferentes**: Teste o cliente e o servidor em computadores diferentes para simular uma rede real e ver melhor as diferenças entre TCP e UDP.
- **Tamanho do Arquivo**: Se tiver interesse, envie arquivos maiores e veja como cada protocolo lida com o aumento de dados, especialmente com UDP.

## Conclusão

Com este projeto, você verá como TCP e UDP têm comportamentos bem diferentes. Dependendo da sua necessidade (rapidez ou confiabilidade), você pode escolher o protocolo mais adequado para a comunicação em rede.
