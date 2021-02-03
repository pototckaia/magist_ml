import numpy as np

n, k = list(map(int, input().split()))
features = input().lower().strip().split()
trainY = []
trainFeature = [[] for _ in range(k)]
for i in range(n):
    data = input().lower().strip().split()
    trainY.append(int(data[-1]))
    for j in range(k):
        trainFeature[j].append(data[j])

m = int(input())
testX = []
for i in range(m):
    testX.append(input().lower().strip().split())

bestFeatureIndex = 0
bestOneRule = {}
bestTotalError = 0
for featureIndex in range(k):

    oneRule = {}
    totalTrueY = 0

    uniqueFeatures = np.unique(trainFeature[featureIndex])
    for uniqueFeature in uniqueFeatures:
        trueCls = len(list(filter(lambda x: x[0] == 1 and x[1] == uniqueFeature, 
                                zip(trainY, trainFeature[featureIndex]))))
        falseCls = len(list(filter(lambda x: x[0] == 0 and x[1] == uniqueFeature, 
                                zip(trainY, trainFeature[featureIndex]))))
        
        if trueCls >= falseCls:
            totalTrueY += trueCls
            oneRule[uniqueFeature] = 1
        else:
            totalTrueY += falseCls 
            oneRule[uniqueFeature] = 0

    totalError = totalTrueY / n
    if totalError > bestTotalError:
        bestFeatureIndex, bestTotalError, bestOneRule = featureIndex, totalError, oneRule


for x in testX:
    print(bestOneRule[x[bestFeatureIndex]])