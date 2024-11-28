# Diário em C

Bem-vindo ao Diário em C – um projeto inovador que combina simplicidade e organização para registrar suas memórias e experiências! Desenvolvido com foco em aprendizado e eficiência, este diário utiliza uma estrutura em árvore binária para facilitar a organização e busca de entradas, e um sistema de persistência baseado em arquivos para garantir que suas anotações estejam sempre salvas.

Além disso, o projeto inclui:

**Validação inteligente de dados** para garantir entradas precisas e confiáveis.
**Menu interativo** para adicionar, listar, buscar e excluir notas com facilidade.

![image](https://github.com/user-attachments/assets/1f854c6a-4e25-4129-b061-cd48d08bf6fd)

## Funcionalidades

**Organização por Árvore Binária:**
Estrutura eficiente para armazenar e buscar entradas por data e título.

**Persistência de Dados em Arquivo:**
Armazena e recupera informações do diário utilizando um arquivo de texto (diario.txt).

**Validação de Dados:**
Verifica se as datas estão em formato válido e evita entradas retroativas, garantindo a integridade das informações.

**Menu Interativo:**
Oferece opções para adicionar, listar, ler e excluir notas do diário de forma simples e intuitiva.

## Menu

- **Adicionar Nota** Permite criar uma nova anotação fornecendo uma data, um título e o conteúdo da nota.
- **Ler diário** Exibe todas as notas disponíveis no diário e permite selecionar uma nota específica para leitura.
- **Excluir Nota** Remove uma nota específica do diário com base na data e no título fornecidos.
- **Sair** Salva todas as notas no arquivo diario.txt e encerra o programa.

![image](https://github.com/user-attachments/assets/56e24fb7-32c4-4543-9bb2-cc8346e0c177)

## 1. Adicionar Nota

**Solicita:**

Data: No formato DD/MM/AAAA.
Valida se a data é futura ou retroativa.
Título: Nome identificador da nota.
Títulos vazios não são aceitos.
Conteúdo: O texto da nota.

**Validações:**

A data deve ser válida e no formato correto.
Não é permitido inserir uma data retroativa.

![image](https://github.com/user-attachments/assets/1ea1b517-e728-40dd-8115-b7663815650f)


## 2. Ler Diário

Exibe todas as notas com data e título.
Permite abrir uma nota específica para visualizar o conteúdo completo.

Usuário seleciona uma nota:

![image](https://github.com/user-attachments/assets/2cca41dd-b364-4b5f-ab05-2a119edd3b7f)

## 3. Excluir Nota

Solicita:

Data: A data da nota a ser excluída.
Título: O título da nota.
Remove a nota da estrutura de árvore e confirma ao usuário. Caso não encontre a nota, exibe uma mensagem.

![image](https://github.com/user-attachments/assets/e9fdd975-ec7e-4f39-8329-8d17e540a7ef)

# Estrutura do Projeto

Estrutura da Árvore
Utiliza uma árvore binária para armazenar e organizar as notas.
Cada nó contém:
Data
Título
Texto da nota
Ponteiros para os filhos esquerdo e direito

Organização do Código
Funções principais:
adicionarNota(): Adiciona uma nova nota à árvore.
exibirArvore(): Lista todas as notas.
lerNota(): Lê uma nota específica.
excluirNo(): Remove uma nota da árvore.
salvarDiario() e carregarDiario(): Gerenciam a persistência de dados.

# Melhorias Futuras

1. Segurança com chave/cadeado: Adicionar autenticação para proteger o acesso ao diário.
2. Exportação de Notas: Permitir salvar notas em formatos como PDF ou HTML.
3. Interface Gráfica: Melhorar a usabilidade com uma interface amigável.
4. Suporte a busca avançada: Buscar notas por palavras-chave no texto.

## Funcionalidades

- [x] Menu
- [x] Adicionar uma nova nota com data e título
- [x] Verificação de data retroativa
- [x] Validação de título e conteúdo
- [x] Estrutura de árvore binária para armazenar notas
- [ ] Implementação de segurança com chave/cadeado

