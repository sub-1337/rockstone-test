
## Анализ Client.cpp

Я нашёл несколкьо мест, которые могнут стать источником ошибки.

1) player испоьзуется, но нигде не инициализируется, даже 
не проверяется.

2) Функция void `Client::login(const client::Packet *packet)` определена
так, но в неё передаётся `const server::Packet &packet` в
`void Client::on_packet(const server::Packet &packet)`. Это
разные типы и я не уверен что этот код может отработать.

3) В той же функции `void Client::login(const client::Packet *packet)`
Мы передаём `LoginData data` по ссылке. Это потенционально висячий указатель.


