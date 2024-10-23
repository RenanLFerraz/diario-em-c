# Diário em C

Este é um projeto de um diário desenvolvido em C. O objetivo é criar uma aplicação que utiliza árvores para estruturar as entradas do diário e um banco de dados (SQLite) para armazenar as informações de forma persistente. Além disso, o diário contará com um sistema de chave/cadeado para proteger as entradas.

![image](https://github.com/user-attachments/assets/1f854c6a-4e25-4129-b061-cd48d08bf6fd)

## Funcionalidades

- **Armazenamento em árvore não binária** para facilitar a busca por datas e entradas.
- **Banco de dados SQLite** para armazenar as escritas do diário.
- **Sistema de segurança** com chave para garantir a privacidade das entradas.

## Menu

- **Adicionar Nota** Para registrar nova anotação no diário.
- **Ler diário** Ler registro de uma data.
  - **Buscar data** Realizar busca pela data especifica.
- **Excluir Nota** Remover alguma anotação de acordo com a data de remoção.
- **Sair**

![image](https://github.com/user-attachments/assets/0a670c47-56c1-4eab-ba69-fd679af1b16f)

## 1. Adicionar Nota

- Implementação de validações para data e título.
- Incluída verificação para impedir datas retroativas.
- Melhorias no fluxo de interação com o usuário.

![image](https://github.com/user-attachments/assets/0cfcfcd7-d52d-4493-9339-b53101e98777)

# Planos

## Funcionalidades

- [x] Menu
- [x] Adicionar uma nova nota com data e título
- [x] Verificação de data retroativa
- [x] Validação de título e conteúdo
- [ ] Estrutura de árvore não binária para armazenar notas
- [ ] Implementação de segurança com chave/cadeado
- [ ] Integração com banco de dados para persistência

