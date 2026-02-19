
def f1(state: str) -> int:

    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(not first_bit and not second_bit and not third_bit and not fourth_bit)
    return result


def f2(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and not second_bit and not third_bit and not fourth_bit)
    return result


def f3(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(not first_bit and second_bit and not third_bit and not fourth_bit)
    return result


def f4(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and second_bit and not third_bit and not fourth_bit)
    return result


def f5(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(not first_bit and not second_bit and third_bit and not fourth_bit)
    return result


def f6(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and not second_bit and third_bit and not fourth_bit)
    return result


def f7(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(not first_bit and second_bit and third_bit and not fourth_bit)
    return result


def f8(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and second_bit and third_bit and not fourth_bit)
    return result


def f9(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and second_bit and third_bit and fourth_bit)
    return result


def f10(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and not second_bit and not third_bit and fourth_bit)
    return result


def f11(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(not first_bit and second_bit and not third_bit and fourth_bit)
    return result


def f12(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and second_bit and not third_bit and fourth_bit)
    return result


def f13(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(not first_bit and not second_bit and third_bit and fourth_bit)
    return result


def f14(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and not second_bit and third_bit and fourth_bit)
    return result


def f15(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(not first_bit and second_bit and third_bit and fourth_bit)
    return result


def f16(state: str) -> int:
    first_bit = int(state[3])
    second_bit = int(state[2])
    third_bit = int(state[1])
    fourth_bit = int(state[0])

    result = int(first_bit and second_bit and third_bit and fourth_bit)
    return result
