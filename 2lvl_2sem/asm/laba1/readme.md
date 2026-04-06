Чтобы запустить:
1. Поставить пакеты на арче:
```shell
sudo pacman -S nasm gcc
```
- `nasm` - ассемблер
- `gcc` - компилятор

2. Скомпилить ассемблер файл:
```shell
nasm -f elf64 laba1.asm -o lab1.o
```

3. Линкуем
```shell
gcc lab1.o -o lab1 -no-pie
```

4. Запускаем
```shell
./laba1
```
