
.section .boot
.global _start
_start:
    csrr t0, mhartid
    bnez t0, 2f
    csrw satp, zero

.option push
.option norelax
    la gp, global_pointer
.option pop

    la a0, bss_start
    la a1, bss_end

bss_init:
    bgeu a0, a1, 1f
    sd zero, (a0)
    addi a0, a0, 8
    j bss_init

1:
    la t1, arch_main
    csrw mepc, t1
    tail arch_main
2:
    wfi
    j 2b
