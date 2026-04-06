extern printf    ; Подключаем функцию вывода на экран из библиотеки C
global main      ; Указываем точку входа

section .data
    ; dq - это "define quadword", 64-битные переменные
    var_a dq -16
    var_b dq 39
    var_c dq 14
    var_d dq 28
    
    ; Строка-шаблон для вывода результата (как в C: "Result: %d\n")
    fmt_string db "Результат формулы: %d", 10, 0 

section .text
main:
    push rbp            ; Техническая рутина: выравниваем стек

    ; --- ШАГ 1: ((b + 5) Div a) ---
    mov rax, [var_b]    ; RAX = 39
    add rax, 5          ; RAX = 44
    
    cqo                 ; Расширяем знак RAX в RDX (нужно перед делением в 64-битах)
    idiv qword [var_a]  ; Делим на -16. Результат (-2) лежит в RAX
    
    mov r8, rax         ; Прячем -2 в регистр R8


    ; --- ШАГ 2: c^2 ---
    mov rax, [var_c]    ; RAX = 14
    imul rax, [var_c]   ; RAX = 14 * 14 = 196
    
    mov r9, rax         ; Прячем 196 в регистр R9


    ; --- ШАГ 3: 4 * d ---
    mov rax, [var_d]    ; RAX = 28
    imul rax, 4         ; RAX = 28 * 4 = 112


    ; --- ШАГ 4: Собираем ((b+5) Div a) - c^2 + 4*d ---
    ; Сейчас: R8 = -2, R9 = 196, RAX = 112
    sub r8, r9          ; R8 = -2 - 196 = -198
    add r8, rax         ; R8 = -198 + 112 = -86
    ; Итоговый ответ (-86) лежит в R8


    ; --- ШАГ 5: Вывод на экран ---
    mov rdi, fmt_string ; 1-й аргумент для printf (строка-шаблон)
    mov rsi, r8         ; 2-й аргумент для printf (наше число)
    mov rax, 0          ; Требование Linux: обнулить RAX перед вызовом printf
    call printf         ; Вызываем печать

    ; --- ЗАВЕРШЕНИЕ ---
    pop rbp             ; Возвращаем стек на место
    mov rax, 0          ; Код возврата 0 (всё прошло успешно)
    ret                 ; Выход из программы
