# ⛳ Smart Bay Lighting Automation - ESP32 MQTT Node

Project ini adalah implementasi sistem *Smart Bay Lighting* berbasis IoT menggunakan mikrokontroler **ESP32** dan protokol **MQTT**. Kodingan ini dirancang untuk diintegrasikan dengan *Local Edge Gateway*, bertugas sebagai *node* eksekutor yang mengontrol *relay* lampu berdasarkan jadwal *booking* secara *real-time*.

## 📖 Deskripsi Sistem
Perangkat dikonfigurasikan dengan pendekatan **Local-First (Edge Computing)**. ESP32 beroperasi sebagai perangkat pasif (*dumb device*) yang hanya mengeksekusi perintah dari *server* lokal (MQTT Broker) tanpa perlu terhubung langsung ke layanan *Cloud*. Hal ini menjamin stabilitas operasional di lapangan meskipun koneksi internet eksternal terputus.

## ✨ Fitur & Konsep Utama yang Diterapkan

1. **Idempotency Handling:** Sistem dilengkapi pelindung pesan ganda (*duplicate message*). Jika jaringan WiFi tidak stabil dan alat menerima *payload* JSON yang sama berulang kali (ID booking dan event sama), ESP32 hanya akan mengeksekusinya satu kali untuk mencegah *relay* berkedip/rusak.
2. **Spesific Topic Subscription:** Perangkat hanya melakukan *subscribe* pada topiknya sendiri secara spesifik (misal: `venue/golf/bay-07/light/command`) tanpa *wildcard*, demi efisiensi RAM mikrokontroler.
3. **QoS 1 (At least once):** Menjamin perintah dari server terverifikasi sampai ke alat.
4. **Auto-Reconnect:** Terintegrasi dengan fungsi standar MQTT untuk otomatis mencoba terhubung kembali (*reconnect*) jika koneksi WiFi atau Broker terputus.

## 🛠️ Kebutuhan Hardware & Software
* **Hardware:** ESP32 Development Board, Modul Relay (3.3V / 5V), Kabel Jumper.
* **Software:** VS Code + PlatformIO (Sangat direkomendasikan) atau Arduino IDE.
* **Dependencies (Library):**
  * `PubSubClient` (untuk komunikasi MQTT)
  * `ArduinoJson` (untuk parsing *payload* JSON)

## 🚀 Cara Instalasi & Upload

1. **Clone Repository:**
   ```bash
   git clone [https://github.com/dimpras1/testmqtt.git](https://github.com/dimpras1/testmqtt.git)
