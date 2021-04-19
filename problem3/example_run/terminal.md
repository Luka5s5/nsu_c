При первом запуске сгенерировался `input.txt`, чтобы тестилось на одинаковых данных во второй раз вместо генератора передал тест.
```console
lukasss@LukaSsS-Laptop:/.../NSU_prog/problem3$ g++ test.c -w -o test
lukasss@LukaSsS-Laptop:/.../NSU_prog/problem3$ g++ C_main_solution.c -w -o fast
lukasss@LukaSsS-Laptop:/.../NSU_prog/problem3$ g++ C_slow_sort.c -w -o slow
lukasss@LukaSsS-Laptop:/.../NSU_prog/problem3$ ./test slow gen_small_alot.c 3
Generating input...
Generated input!
running test 1...
running test 2...
running test 3...
run 1, time 17.700000s, AC
run 2, time 17.760000s, AC
run 3, time 21.660000s, AC
Uncorrected SD: 1.852782, corrected SD: 2.269185
Max time: 21.660000, min time: 17.700000
lukasss@LukaSsS-Laptop:/.../NSU_prog/problem3$ ./test fast input.txt 3
Generating input...
cp: 'input.txt' and 'input.txt' are the same file
Generated input!
running test 1...
running test 2...
running test 3...
run 1, time 0.470000s, AC
run 2, time 0.510000s, AC
run 3, time 0.450000s, AC
Uncorrected SD: 0.024944, corrected SD: 0.030551
Max time: 0.510000, min time: 0.450000
```