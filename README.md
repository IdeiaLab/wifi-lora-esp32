# Emissão e recepção de pacotes LoRa

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



<!-- ![esp-lora-enviador](https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/fed75b09-6dcd-4acf-a47e-1e6ec7b025ac "Emissor LoRa") -->

<h3>Receptor</h3>
<div align='left'>
  No módulo receptor (pasta LoRa_recv) há apenas o arquivo LoRa_recv.ino
 <dl>
    <dt>LoRa_recv.ino</dt>
      <dd>
        O código trata das inicializações, como no emissor, e aguarda a emissão de pacotes, caso receba, este é mostrado no
        display OLED, bem como o <strong>RSSI</strong>, que é a força do sinal, e a "latência", que é a diferença de tempo 
        entre o último pacote e o atual.
      </dd>
 </dl>
</div>

<div align='center'>
  <img src='https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/a1938a02-1822-468a-9ed3-7859bb2eefb7'
     alt='Receptor LoRa recebendo pacote' style="width:30vw"/>
  <img src='https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/001dfa38-1b9e-409b-91f4-bf01c54ad85d'
       alt='Receptor LoRa aguardando pacote' style="width:30vw"/>
</div>

     
<!-- ![esp-lora-receptor](https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/a1938a02-1822-468a-9ed3-7859bb2eefb7 ) -->
<!-- ![esp-lora-receptor2](https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/001dfa38-1b9e-409b-91f4-bf01c54ad85d) -->

