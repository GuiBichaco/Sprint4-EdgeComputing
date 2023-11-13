``` Projeto para a matéria de Edge computing e computer Systems da faculdade FIAP - para o trabalho Challenge 2023 em conjunto e parceria com a IBM 

**APLICAÇÃO IoT - SMART LIGHT**


Nós fundadores e desenvolvedores da SMART LIGHT, produzimos um projeto em IoT com a placa ESP32, onde com o PHOTORESSISTOR LDR iremos capitar a intensidade luminosa do local e assim conforme
a indicação dos leds executar ações dentro de sua residência, os leds indicam se a carga luminosa está adequada para o fincionamento das atividades.  

Essa aplicação pode ser facilmente projetada por pessoas fora da área com esta documentação.

Em caso de ter os sistemas listados em sua máquina no site dos mesmos, é de fácil compreensão a instalação.


Conceito de IoT:

A Internet das Coisas (IoT) é uma rede de objetos físicos com sensores e conectividade à internet, que coletam dados do ambiente ou do próprio dispositivo e os enviam para servidores ou outros dispositivos para tomada de decisões. A IoT desempenha um papel importante em áreas como automação, saúde, sustentabilidade e cidades inteligentes, melhorando a eficiência e a qualidade de vida da sociedade.

**-> Arduino IDE**

Com o software Arduino IDE, você deverá desenvolver seu código de acordo com o uso da sua placa. A linguagem adequada é o C++ (nossos códigos-fonte estarão mais abaixo desta documentação). A plataforma Arduino IDE é responsável pela compilação do código programado para o seu circuito em C++ para ser lido pela firmware da placa.

Ao terminar o código, vá em "Verify", "Sketch", "Export Compiled Binary". Logo em seguida, vá em "File", "Save As" e salve o arquivo no local desejado.

**-> SimulIDE**

**-> Wokwi**

Com o software online de acesso (https://wokwi.com) WOKWI, você deverá desenvolver seu código de acordo com o uso da sua placa. A linguagem adequada é o C++ (nossos códigos-fonte estarão mais abaixo desta documentação). A plataforma Wokwi é responsável pela compilação do código programado para o seu circuito em C++ para ser lido pela firmware da placa.
Ele já da o suporte para a construção do código em .ino, próprio para a aplicação no software ARDUINO para aplicação em projetos físicos. 

Ao terminar o código, vá em "Save". Logo em seguida, vá no "Play" verde e execute o projeto.


**-> Node-Red**

Ele será responsável pela construção do fluxo do servidor local, onde conecta todos os passos até aqui em um único nó de conexão. Via protocolo de comunicação MQTT, ele será conectado a um servidor próprio para a construção das devices e do dashboard.

A instalação do Node-Red é simples:

- Faça a instalação do Node.js (Versão LTS) (node-version) - [www.nodejs.org](www.nodejs.org)
- Abra o CMD e digite (npm install -g --unsafe-perm node-red)
- Para acessar o serviço, após instalado, digite no cmd: node-red
- Acesse no browser: [http://localhost:1880](http://localhost:1880)

Após abrir o programa, vá nas três barrinhas no canto superior direito, "Gerenciar Paletas" e baixe a biblioteca node-red-dashboard.

O código fonte de exemplo está na documentação do projeto, nele conectamos duas portas de entrada de comandos (inject) para a ligação MQTT com os dois tópicos configurados no MQTT OUT

Para dúvidas, contate a equipe técnica:

- Enzo de Oliveira Cunha - 550985
- Guilherme Catelli Bichaco - 97989
- Lucas Almeida de Siqueira - 551854
- Lucas Laia Manentti - 97709
- Vinicius Sobreira Borges - 97767