# qr_to_array.py
#
# URLからQRコードの2次元配列を生成して、
# C/C++に貼れる形式で出力する
#
# pip install qrcode[pil]

import qrcode

URL = "https://ishikishik.github.io/otter-device-link/"

qr = qrcode.QRCode(
    version=None,  # 自動
    error_correction=qrcode.constants.ERROR_CORRECT_L,
    box_size=1,
    border=0
)

qr.add_data(URL)
qr.make(fit=True)

matrix = qr.get_matrix()

size = len(matrix)

print(f"// size = {size} x {size}")
print()

print(f"const uint8_t qr[{size}][{size}] = {{")

for row in matrix:
    line = ", ".join("1" if cell else "0" for cell in row)
    print(f"  {{{line}}},")

print("};")