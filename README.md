# name
PASSGEN

## Overview
C言語で作られたランダムなパスワードを生成するコマンドラインツールです。

## Image
![image](/assets/image.png)

## How to start
 - exeファイルから起動する方法
 1. GithubのReleasesからファイルをダウンロードする
 2. ターミナルから実行
 - ソースコードから起動する方法
 1. GCCでコンパイルして生成されたexeファイルをターミナルで実行

## Usage
1. ターミナルに```passgen.exe <パスワード長> <生成数> [オプション]```を指定して実行
```bash
# 基本的な使い方（小文字・大文字・数字を含む）
passgen 12 5

# 記号を含める
passgen 16 3 -s

# 数字と大文字を除外
passgen 8 4 -n -u

# 数字だけのパスワード
passgen 10 2 -l -u -s
```

## Option
| フラグ | 効果 | デフォルト |
|--------|------|-----------|
| `-s` | **記号を有効化** (`!@#$%^&*()`) | 無効 |
| `-n` | 数字を**無効化** | 有効 |
| `-u` | 大文字を**無効化** | 有効 |
| `-l` | 小文字を**無効化** | 有効 |

## Features
- パスワードの文字数の指定
- パスワードを生成する数の指定
- パスワードに使用する文字種の指定

## Author
- [Github](https://github.com/anpontannahito)
- [ホームページ](https://anpontannahito.github.io/)

## Licence
[MIT License](https://opensource.org/license/mit)<br>
このソフトウェアはMIT Licenseの条件の下で配布されます。
