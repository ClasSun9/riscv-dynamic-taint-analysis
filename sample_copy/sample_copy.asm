.global _start

read:
    mv s1, a7
    li a7, 63
    ecall
    mv a7, s1
    ret

write:
    mv s1, a7
    li a7, 64
    ecall
    mv a7, s1
    ret

exit:
    li a7, 93
    ecall

copy:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd s0, 0(sp)
    
    loop:
        lb a3, 0(a1)
        sb a3, 0(a0)
        addi a0, a0, 1
        addi a1, a1, 1
        addi a2, a2, -1
        bne a2, zero, loop

    ld ra, 8(sp)
    ld s0, 0(sp)
    addi sp, sp, 16
    ret

main:
    addi sp, sp, -48
    sd ra, 40(sp)
    sd s0, 32(sp)

    li a2, 16
    mv a1, sp
    li a0, 0
    jal read

    li a2, 16
    mv a1, sp
    la a0, dst
    jal copy

    ld ra, 40(sp)
    ld s0, 32(sp)
    addi sp, sp, 48
    ret

_start:
    jal ra, main
    li a0, 0
    jal zero, exit

.section .data
dst: .byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
