man pmap

ps auxw
htop

pmap -X (pid)

# 对 memory-user 使用 pmap -X (pid) 命令
# 由 memory-user libc.so.6 ld-linux-x86-64.so.2 [stack] [vvar] [vdso] 组成

# 使用 参数 10 和 1000 二者 size 几乎相同, 而 Referenced 略有不同
