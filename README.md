# Emissão e recepção de pacotes LoRa
### Informações
  <div align='left'>
    Ferramentas utilizadas: 
    <ul>
      <li>Arduino IDE</li>
      <li>Arduino C</li>
      <li>C++</li>
    </ul>
    Placa utilizada: 
    <ul><li>Heltec Wifi Lora 32 V2</li></ul>
    Bibliotecas: 
    <ul>
      <li>EspLoRa</li>
      <li>Wi-Fi</li>
      <li>AdafruitSSD3306</li>
      <li>AdafruitGFX</li>
      <li>SPI</li>
    </ul>
    <a href='https://RandomNerdTutorials.com/ttgo-lora32-sx1276-arduino-ide/'>CÓDIGO BASE</a>
  </div>
  <hr/>
<h3>Emissor</h3>
<div align='left'>
  Na pasta LoRa_send, módulo de envio, se encontram 3 arquivos: "LoRa_send.ino", "RandomDelay.hpp" e "RandomDelay.cpp". <br/>
  <dl>
    <dt>RandomDelay.hpp</dt>
      <dd>
        Este arquivo contém a declaração do namespace RandomDelay que contém a função randomDelay, que retorna um 
        número aleatório dados os limites inferior e superior.
      </dd>
      <dt>RandomDelay.cpp</dt>
      <dd>
        Este arquivo contémm a definição da função randomDelay, apesar de muito simples, serve como exemplo de 
        como implementar código C++ puro a qualquer projeto Arduino.
      </dd>
      <dt>LoRa_send.ino</dt>
      <dd>
        Esse é o arquivo mais importante da pasta, claro. O <i>sketch</i> traz consigo, por exemplo, inicialização 
        do Wi-Fi, inicialização do display OLED e do LoRa, no display é possível ver algumas informações: o pacote
        que está sendo enviado, o contador de envios, o tempo corrido desde a inicialização e o tempo até o próximo
        pacote
      </dd>
  </dl>
</div>

<div align='center'>
    <img src='https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/fed75b09-6dcd-4acf-a47e-1e6ec7b025ac'
     alt='Emissor LoRa enviando pacote' style="width:45vw;"/>
</div>
<hr/>
<!-- ![esp-lora-enviador](https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/fed75b09-6dcd-4acf-a47e-1e6ec7b025ac "Emissor LoRa") -->

<h3>Receptor</h3>
<div align='left'>
  No módulo receptor (pasta LoRa_recv) há apenas o arquivo LoRa_recv.ino
 <dl>
    <dt>LoRa_recv.ino</dt>
      <dd>
        O código trata das inicializações, como no emissor, e aguarda a emissão de pacotes, caso receba, este é mostrado no
        display OLED, bem como o <strong>RSSI</strong>, que é a força do sinal, e a "latência", que é a diferença de tempo 
        entre o último pacote e o atual. Caso o receptor esteja aguardando por um período de tempo estabelecido no programa,
        ele mostra uma tela de aguardo, que mostra o último pacote recebido e um texto que mostra que o receptor está esperando
        por mais pacotes.
      </dd>
 </dl>
</div>

<div align='center'>
  <img src='https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/a1938a02-1822-468a-9ed3-7859bb2eefb7'
     alt='Receptor LoRa recebendo pacote' style="width:30vw"/>
  <img src='https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/001dfa38-1b9e-409b-91f4-bf01c54ad85d'
       alt='Receptor LoRa aguardando pacote' style="width:31vw"/>
</div>

     
<!-- ![esp-lora-receptor](https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/a1938a02-1822-468a-9ed3-7859bb2eefb7 ) -->
<!-- ![esp-lora-receptor2](https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/001dfa38-1b9e-409b-91f4-bf01c54ad85d) -->

