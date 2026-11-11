//QRcodeを書いてみる。


#include <LovyanGFX.hpp>
#include "lgfxesp32c3.hpp"

MyLGFX lcd;

// ===== QR配列をここに貼る =====
const uint8_t qr[29][29] = {
  {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
  {1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0},
  {0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1},
  {0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
  {0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
  {1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
  {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0},
  {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0},
  {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
};


// ===== 設定 =====
const int DOT_SIZE = 3;
const int SENSOR_PIN = 4;   // 受光部の ADC ピン(kawaeyes v2 基板の ALS)
const int SENSOR_PWR = 3;   // 受光部の電源(HIGH で ON)
unsigned long T_MS = 0;     // 点滅の基本の長さ。開始の合図から自動で測る(Web 側と合わせなくてよい)

const uint32_t BG_COLOR   = 0x000000U;
const uint32_t MAIN_COLOR = 0x00FF00U;

// ===== 受信結果 =====
String receivedSsid = "";
String receivedPass = "";
String currentBits = "";
int receivedSum = -1;         // 受け取ったチェックサム(-1 = まだ)
String status = "waiting";    // 画面に出す状態

enum ReceiveMode {
  WAIT_START,      // 開始の合図の前半(緑 8T・黒 4T)を待つ
  WAIT_HEADER,     // 開始の合図の後半(緑 4T・黒 1T)を待つ
  READ_SSID,
  READ_PASSWORD,
  READ_SUM,        // チェックサム 1 バイト
  FINISHED
};

ReceiveMode mode = WAIT_START;

// ===== 光の状態検出用 =====
bool lastLight = false;
unsigned long lastEdgeTime = 0;
unsigned long greenDuration = 0;
unsigned long blackDuration = 0;

// しきい値は自動で決める: 最近の一番暗い値(lo)と一番明るい値(hi)の中間
// lo / hi は少しずつ中央へ戻すので、部屋やスマホの明るさが変わっても追いかける
int lo = 4095, hi = 0;
unsigned long lastDecay = 0;
const int MIN_SWING = 30;   // 明暗の差がこれより小さいうちは「点滅していない」とみなす

// --------------------------------
// 画面描画
// --------------------------------

void drawQR() {
  int qrSize = sizeof(qr) / sizeof(qr[0]);

  int offsetX = 0;
  int offsetY = 0;

  for (int y = 0; y < qrSize; y++) {
    for (int x = 0; x < qrSize; x++) {
      if (qr[y][x]) {
        lcd.fillRect(
          offsetX + x * DOT_SIZE,
          offsetY + y * DOT_SIZE,
          DOT_SIZE,
          DOT_SIZE,
          MAIN_COLOR
        );
      }
    }
  }
}

void drawStaticScreen() {
  lcd.fillScreen(BG_COLOR);

  // 左上にQR
  drawQR();

  // 右側に説明
  lcd.setTextColor(MAIN_COLOR, BG_COLOR);
  lcd.setTextSize(1);

  int x = 115;
  int y = 8;

  lcd.setCursor(x, y);
  lcd.println("Otter Device Link");

  y += 20;
  lcd.setCursor(x, y);
  lcd.println("1. Scan QR");

  y += 16;
  lcd.setCursor(x, y);
  lcd.println("2. Press sensor");

  y += 16;
  lcd.setCursor(x, y);
  lcd.println("   to upper half");

  y += 16;
  lcd.setCursor(x, y);
  lcd.println("   of phone screen");

  y += 16;
  lcd.setCursor(x, y);
  lcd.println("3. Input SSID/PASS");

  y += 16;
  lcd.setCursor(x, y);
  lcd.println("4. Push START");

  // 下側に受信欄
  lcd.drawRect(0, 135, 320, 105, MAIN_COLOR);

  lcd.setCursor(8, 145);
  lcd.println("Received data");

  lcd.setCursor(8, 165);
  lcd.println("SSID:");

  lcd.setCursor(8, 195);
  lcd.println("PASS:");
}

void updateReceivedArea() {
  // 表示欄だけ黒で消す
  lcd.fillRect(55, 160, 260, 70, BG_COLOR);

  lcd.setTextColor(MAIN_COLOR, BG_COLOR);
  lcd.setTextSize(1);

  lcd.setCursor(55, 165);
  lcd.print(receivedSsid);

  lcd.setCursor(55, 195);
  lcd.print(receivedPass);

  lcd.setCursor(8, 220);
  lcd.print("bits:");
  lcd.print(currentBits);
  lcd.print("        ");

  lcd.setCursor(160, 220);
  lcd.printf("T=%lums %s", T_MS, status.c_str());
}

// --------------------------------
// 受信デコード
// --------------------------------

bool nearUnit(int value, int target) {
  // Tの何倍かをざっくり判定
  // 許容幅は広め。あとで調整してください。
  return abs(value - target) <= 1;
}

int toUnit(unsigned long durationMs) {
  if (T_MS == 0) return 0;
  return (durationMs + T_MS / 2) / T_MS;
}

void resetReceive() {
  receivedSsid = "";
  receivedPass = "";
  currentBits = "";
  receivedSum = -1;
  mode = WAIT_START;
  updateReceivedArea();
}

// SSID とパスワードの全バイトの合計の下位 8 ビット(Web 側の checksum() と同じ)
int calcSum() {
  int sum = 0;
  for (char c : receivedSsid + receivedPass) sum = (sum + (uint8_t)c) & 0xFF;
  return sum;
}

void addBit(int bit) {
  currentBits += bit ? "1" : "0";

  // 8bitたまったら1文字に変換
  if (currentBits.length() >= 8) {
    int code = 0;

    for (int i = 0; i < 8; i++) {
      code <<= 1;
      if (currentBits[i] == '1') {
        code |= 1;
      }
    }

    // UTF-8 1バイト、つまりASCIIだけ採用
    if (code <= 0x7F) {
      if (mode == READ_SSID) {
        receivedSsid += char(code);
      } else if (mode == READ_PASSWORD) {
        receivedPass += char(code);
      }
    }
    if (mode == READ_SUM) receivedSum = code;   // チェックサムは 0x80 以上もありうる

    currentBits = "";
    updateReceivedArea();
  }
}

void handlePulse(unsigned long gMs, unsigned long bMs) {
  // 開始の合図の前半(緑 8T・黒 4T): 緑が黒のおよそ 2 倍の組。ここから T を測る
  if (mode == WAIT_START || mode == FINISHED) {
    if (gMs >= 160 && gMs > bMs * 16 / 10 && gMs < bMs * 24 / 10) {   // 緑 ≒ 黒 × 2(T は 20ms 以上)
      T_MS = (gMs + bMs) / 12;
      mode = WAIT_HEADER;
      status = "start";
      updateReceivedArea();
    }
    return;
  }

  int g = toUnit(gMs);
  int b = toUnit(bMs);

  Serial.print("G=");
  Serial.print(g);
  Serial.print(" B=");
  Serial.println(b);

  // 開始の合図の後半(緑 4T・黒 1T)
  if (mode == WAIT_HEADER) {
    if (nearUnit(g, 4) && nearUnit(b, 1)) {
      receivedSsid = "";
      receivedPass = "";
      currentBits = "";
      receivedSum = -1;
      mode = READ_SSID;
      status = "receiving";
    } else {
      mode = WAIT_START;   // 合図ではなかった
      status = "waiting";
    }
    updateReceivedArea();
    return;
  }

  // G4 B1 は区切り(SSID → パスワード → チェックサム)か終わり
  if (nearUnit(g, 4) && nearUnit(b, 1)) {
    currentBits = "";
    if (mode == READ_SSID) {
      mode = READ_PASSWORD;
    } else if (mode == READ_PASSWORD) {
      mode = READ_SUM;
    } else if (mode == READ_SUM) {
      mode = FINISHED;
      status = (receivedSum == calcSum()) ? "OK" : "NG";   // NG なら読み違いがある
    }
    updateReceivedArea();
    return;
  }

  // 0: green T, black T
  if (nearUnit(g, 1) && nearUnit(b, 1)) {
    addBit(0);
    return;
  }

  // 1: green T, black 3T
  if (nearUnit(g, 1) && nearUnit(b, 3)) {
    addBit(1);
    return;
  }
}

void readSensor() {
  int value = analogRead(SENSOR_PIN);
  unsigned long now = millis();

  // 明るさの範囲を覚え、10ms ごとに少しずつ中央へ戻す
  if (value < lo) lo = value;
  if (value > hi) hi = value;
  if (now - lastDecay >= 10) {
    lastDecay = now;
    if (lo < hi) { lo++; hi--; }
  }
  if (hi - lo < MIN_SWING) return;   // まだ点滅していない

  // しきい値は中間。境目でばたつかないよう、反対側へは幅の 1/8 だけ余分に越えたら切り替える
  int mid = (lo + hi) / 2, margin = (hi - lo) / 8;
  bool light = lastLight ? value > mid - margin : value > mid + margin;

  // 光状態が変化した瞬間だけ処理
  if (light != lastLight) {
    unsigned long duration = now - lastEdgeTime;

    if (lastLight) {
      // 直前まで光っていた → green時間
      greenDuration = duration;
    } else {
      // 直前まで暗かった → black時間
      blackDuration = duration;

      // greenとblackが1セットそろったので判定
      handlePulse(greenDuration, blackDuration);
    }

    lastEdgeTime = now;
    lastLight = light;
  }
}

// --------------------------------
// setup / loop
// --------------------------------

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.setRotation(3);
  lcd.setBrightness(128);

  drawStaticScreen();
  updateReceivedArea();

  pinMode(SENSOR_PWR, OUTPUT);
  digitalWrite(SENSOR_PWR, HIGH);   // 受光部の電源を入れる
  lastLight = false;
  lastEdgeTime = millis();
}

void loop() {
  readSensor();
}