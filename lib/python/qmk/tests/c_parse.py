from qmk.c_parse import extract_enum_from_c_file_as_dict


def test_extract_enum_from_c_file_as_dict():
    test_cases = [
        {
            'input_1': 'enum my_enum {};',
            'input_2': 'my_enum',
            'expected_output': {}
        },
        {
            'input_1': 'enum my_enum { A };',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 0
            }
        },
        {
            'input_1': 'enum my_enum { A = 5, B = 10, C = 15 };',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 5,
                'B': 10,
                'C': 15
            }
        },
        {
            'input_1': 'enum my_enum { A, B = 10, C };',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 0,
                'B': 10,
                'C': 11
            }
        },
        {
            'input_1': 'enum my_enum {\n    A,\n    B, // This comment refers to letter B\n    C\n};',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 0,
                'B': 1,
                'C': 2
            }
        },
        {
            'input_1': 'enum my_enum { A = 0, B = 0, C = 1 };',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 0,
                'B': 0,
                'C': 1
            }
        },
        {
            'input_1': 'enum my_enum {\n    A,\n    B,\n    C\n};\n\nenum my_other_enum {\n  D\n};',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 0,
                'B': 1,
                'C': 2
            }
        },
        {
            'input_1': '/* Valid C comments */\nenum my_enum {\n    A,\n    B,\n    C\n};',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 0,
                'B': 1,
                'C': 2
            }
        },
        {
            'input_1': 'enum my_enum {\n    A,\n    B,\n    C\n};',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 0,
                'B': 1,
                'C': 2
            }
        },
        {
            'input_1': 'enum my_enum {\n    A = 42,\n    B,\n    C\n};',
            'input_2': 'my_enum',
            'expected_output': {
                'A': 42,
                'B': 43,
                'C': 44
            }
        },
    ]

    for test_case in test_cases:
        result = extract_enum_from_c_file_as_dict(test_case["input_1"], test_case["input_2"])
        assert test_case["expected_output"] == result
