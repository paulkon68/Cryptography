import func


# List with the states as strings
states = [bin(i & 0xf)[2:].zfill(4) for i in range(16)]


# Generate the functions that will be called.
# For example, for the function: F = Σ(15), the generate function will return a list with the number 16 as element
def generate_function(number: int) -> list:

    bnum = bin(number)[2:].zfill(16)
    # print(bnum)
    funct_used = []

    # If the function is the F = 0, return
    if int(bnum) == 0:
        return funct_used

    for i in range(1, 17):
        if int(bnum[i-1]):
            funct_used.append(i)

    return funct_used


# Generate the next state of lfsr
def lfsr_next(state: str, func_num: int) -> str:

    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    fun_list = generate_function(func_num)
    # print(fun_list)
    result = 0

    for i in fun_list:

        # print(f"{i}p{result}")
        if i == 1:
            result |= func.f1(state)
        elif i == 2:
            result |= func.f2(state)
        elif i == 3:
            result |= func.f3(state)
        elif i == 4:
            result |= func.f4(state)
        elif i == 5:
            result |= func.f5(state)
        elif i == 6:
            result |= func.f6(state)
        elif i == 7:
            result |= func.f7(state)
        elif i == 8:
            result |= func.f8(state)
        elif i == 9:
            result |= func.f9(state)
        elif i == 10:
            result |= func.f10(state)
        elif i == 11:
            result |= func.f11(state)
        elif i == 12:
            result |= func.f12(state)
        elif i == 13:
            result |= func.f13(state)
        elif i == 14:
            result |= func.f14(state)
        elif i == 15:
            result |= func.f15(state)
        else:
            result |= func.f16(state)

        if result == 1:
            break
    # print(f"res:{result}")
    # print(state)
    state_pr = (int(state) << 1) & 0xf
    state_aftr = state_pr ^ result
    state_aftr = bin(state_aftr)[2:].zfill(4)
    return state_aftr


# Check the period for a given function and a state
def check_period(state: str, func_num: int) -> int:
    starting_state = state
    # zero_state = '0'.zfill(4)
    next_state = state
    period = 0

    state_list = list()

    state_list.append(starting_state)

    # while(next_state := lfsr_next(next_state, func_num)) not in state_list:
    while (next_state := lfsr_next(next_state, func_num)) != starting_state:
        # state_list.append(next_state)
        period += 1
        # print(f"Function: {func_num}, Period: {period}, Starting State: {starting_state}, Next State: {next_state}")

        if period > 15:
            period = -1
            break

        # if next_state == zero_state:
        #     break

    print(f"Function: {func_num}, starting on state: {starting_state!r}, has a period of {period}.")

    return period


func_stats = {}
func_period = []
# def mt(num):
#     for i in range(1, num)


for i in range(1, 65536):
    for j in states:
        func_period.append(check_period(j, i))
    func_stats.setdefault(i, max(func_period))
    func_period = []

max_period_fun = []


# for k, v in func_stats.items():
#     if v == 15:
#         # print(f"Function: {k} - Period: {v}")
#         #     if check_period("0000", k) == 0:
#         #         continue
#             max_period_fun.append(k)

# with open("./results.txt", "w") as file:
#     for k, v in func_stats.items():
#         file.write(f"Function: {k} has a period of {v}\n")
#
#     file.write('+'*120)
#     file.write('\n')
#     file.write("Functions with maximum Period: \n")
#     file.write('+' * 120)
#     file.write('\n')
#     for i in max_period_fun:
#         file.write(f"\t{i}\n")
#     file.write('-'*120)
#
# print(max_period_fun)
# print(generate_function(12))
# print(states[1])
# print(check_period(states[0], 61710))
# print(check_period("1000", 34616))
# print(generate_function(58140))

# maxim_list = []
# for i in states:
#     maxim_list.append(check_period(i, 45676))
#
# print(maxim_list)
print(generate_function(64770))

# for i in states:
#     print(lfsr_next(i, 58140))
