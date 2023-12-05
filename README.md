# Emissão e recepção de pacotes LoRa

<div align='left'>
  Na pasta LoRa_send se encontram 3 arquivos: "LoRa-send.ino", "RandomDelay.hpp" e "RandomDelay.cpp". <br/>
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
      <dt>LoRa-send.ino</dt>
      <dd>
        Esse é o arquivo mais importante da pasta, claro. O _sketch_ traz consigo, por exemplo, inicialização 
        do Wi-Fi, inicialização do display OLED e do LoRa, no display é possível ver algumas informações: o pacote
        que está sendo enviado, o contador de envios, o tempo corrido desde a inicialização e o tempo até o próximo
        pacote
      </dd>
  </dl>
</div>

![esp-lora-enviador](https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/fed75b09-6dcd-4acf-a47e-1e6ec7b025ac "Emissor LoRa")



![esp-lora-receptor](https://github.com/IdeiaLab/wifi-lora-esp32/assets/121146950/a1938a02-1822-468a-9ed3-7859bb2eefb7 "Receptor LoRa")
