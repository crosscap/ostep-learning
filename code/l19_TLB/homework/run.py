#! /usr/bin/env python3

import subprocess
import psutil
import os


def set_cpu_affinity(cpu_id):
    p = psutil.Process(os.getpid())
    p.cpu_affinity([cpu_id])


set_cpu_affinity(0)

i = 1
while i <= 16384:
    sub_p = subprocess.Popen(['./tlb', f'{i}', '100000'])
    sub_p.wait()
    i *= 2
exit(0)
