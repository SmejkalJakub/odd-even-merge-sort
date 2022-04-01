from cmath import phase
import math

def count_processors_for_phase(phaseNumber):
    if(phaseNumber == 0):
        return 1
    elif(phaseNumber == 1):
        return 3
    else:
        return ((2**phaseNumber / 2) + (2*(count_processors_for_phase(phaseNumber - 1))))

def count_processors(numberOfInputs, numberOfPhases):
    numberOfProcessors = 0

    for phase in range(0, numberOfPhases):
        numberOfProcessors += count_processors_for_phase(phase)

    print("Inputs: " + str(numberOfInputs) + " " + "Phases: " + str(numberOfPhases) + " " + "Processors: " + str(numberOfProcessors) + "LogN: " + str(math.log(numberOfInputs,2) * numberOfInputs))


for numberOfPhases in range(1, 20):
    count_processors(2**numberOfPhases, numberOfPhases)