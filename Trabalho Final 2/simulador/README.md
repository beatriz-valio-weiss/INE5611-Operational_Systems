# Simulador de Memória Virtual

## Programas necessários para execução
1) [Visual Studio Code](https://code.visualstudio.com/download)
2) [NodeJS](https://nodejs.org/en/)

## Como instalar NodeJS
Fonte: [Alura](https://www.alura.com.br/artigos/instalando-nodejs-no-windows-e-linux?gclid=CjwKCAjw_tWRBhAwEiwALxFPoap3bWmOvd9EUqPG94gq3f6Ek6XiPhyw5mLc5hcWAmpsGOC4WJdpfRoC-9QQAvD_BwE)

### Windows:
1) Baixar e executar:
   - Acessar a página oficial: https://nodejs.org/en/
   - Baixar a versão LTS (versão mais estável)
   - Executar o arquivo baixado
2) Iniciar a intalação clicando em 'next'
3) Aceitar os termos e licença do programa, prosseguir clicando em 'next'
4) Escolher o local de instalação e prosseguir clicando em 'next'
5) Na parte 'Custom Setup', certificar-se que as seguintes opções estão selecionadas antes de clicar em 'next':
   - ```Node.js runtime``` 
   - ```npm package managere```
   - ```Add to PATHe``` 
6) Selecionar opção de instação automática de outras ferramentas, prosseguir clicando em 'next'
7) Aguardar concluir a instalação
8) Reinicie a máquina para garantir que NodeJS foi escrito corretamente no caminho do ```PATH``` do Windows.

Obs.: Caso a indicação de progresso pareça estagnada por um tempo muito além do que esperaria, você pode pressionar espaço ou esc.

### Linux:

1) Abra o terminal
2) Rode o comando ```sudo apt-get install nodejs```
3) Verificar se a instalação ocorreu corretamente executando no terminal:
   - ```node --version``` 
   - ```npm --version```

## Comando para executar o Simulador no Visual Studio Code
```node .\main.js```
