

# Global Variables
kingdom_animal_map = {
    'land': 'panda',
    'water': 'octopus',
    'ice': 'mammoth',
    'air': 'owl',
    'fire': 'dragon'
}


class TestCase:

    def __init__(self, id, test_type, input):
        self.test = {
            'id': id,
            'type': test_type
        }
        self.input = input

    def change_name(self, new_name):
        self.name = new_name


# Get Character Frequency
def getCharacterFrequnecy(string):
    res = {}
    for c in string:
        if c in res:
            res[c] += 1
        else:
            res[c] = 1
    return res


# Check if Kingdom can be wo
def canWinKingdom(animal, message):
    cf_1 = getCharacterFrequnecy(animal)
    cf_2 = getCharacterFrequnecy(message)

    for key in cf_1:
        if (key not in cf_2) or (cf_2[key] < cf_1[key]):
            return False
    return True


# Solve for given input
def solve(input):

    kingdoms_won = []
    for message in input:
        kingdom = message['kingdom'].lower()
        if kingdom not in kingdom_animal_map:
            raise Exception('Incorrect key."' + kingdom + '" does not exist')
        animal = kingdom_animal_map[kingdom]
        if canWinKingdom(animal, message['secret_code']):
            kingdoms_won.append(kingdom)

    if len(kingdoms_won) >= 3:
        print("King Shan")
    else:
        print("None")

    if len(kingdoms_won) >= 1:
        print(','.join(kingdoms_won))
    else:
        print("None")


# Run a unit test
def runUnitTest(test, input):

    print("-------------------------------")
    print("Solving Test #{:2d} : {}\n".format(test['id'], test['type']))

    try:
        solve(input)
        print("\nTestcase : Passed")
    except Exception as e:
        print("\nTestcase : Failed")
        print(str(e))
    print("-------------------------------\n\n")


if __name__ == "__main__":

    test_cases = []

    # Testcase 1
    input = [
        {
            'kingdom': 'air',
            'secret_code': 'oaaawaala'
        },
        {
            'kingdom': 'land',
            'secret_code': 'a1d22n333a4444p'
        },
        {
            'kingdom': 'ice',
            'secret_code': 'zmzmzmzaztzozh'
        }
    ]
    test_cases.append(TestCase(1, 'Simple 1', input))

    # Testcase 2
    input = [
        {
            'kingdom': 'air',
            'secret_code': 'Let’s swing the sword together'
        },
        {
            'kingdom': 'land',
            'secret_code': 'Die or play the tame of thrones'
        },
        {
            'kingdom': 'ice',
            'secret_code': 'Ahoy! Fight for me with men and money'
        },
        {
            'kingdom': 'water',
            'secret_code': 'Summer is coming'
        },
        {
            'kingdom': 'fire',
            'secret_code': 'Drag on Martin!'
        }
    ]
    test_cases.append(TestCase(2, 'Simple 2', input))

    # Testcase 3
    input = [
        {
            'kingdom': 'air',
            'secret_code': 'l123o123w'
        },
        {
            'kingdom': 'land',
            'secret_code': 'Die or play the tame of thrones'
        },
        {
            'kingdom': 'fire',
            'secret_code': 'Fire is evil'
        }
    ]
    test_cases.append(TestCase(3, 'Not Enough Kingdoms', input))

    for test_case in test_cases:
        runUnitTest(test_case.test, test_case.input)

    print("Done")
