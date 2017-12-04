import math

dist_epi_to_soma = 3000.0


def readfile(filename):
    # Read file
    fi = open(filename)
    lines = fi.read().split("\n")
    data = []

    # Cut first line
    lines = lines[1:]

    # Process lines
    for line in lines:
        item = []
        set = line.split(",")

        if len(set) != 4:
            continue
        item.append(float(set[0]))
        item.append(float(set[1]))
        item.append(float(set[2]))
        data.append(item)
        # print str(set[0]) + " , " + set[1] + " , " + set[2] + " | " + str(item)        # DEBUG parser output

    print("File contains " + str(len(data)) + " lines to parse")
    return data


def calculate_distance(x1, y1, x2, y2):
    return math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))


def calculate_v(g, h):
    if g < 0 or h < 0:
        print "calculate_v: g or h negative: g=" + str(g) + " h=" + str(h)
        return 0
    return math.sqrt(g * h)


def calculate_travel_time(data, total_distance):
    #Time sum
    times = 0.0

    #Statistics variables
    entriesSkipped = 0
    invaliddistance = 0
    invalidcoords = 0
    invalidheights = 0

    #Iterate through time
    for i in range(0, len(data) - 1):
        entry1 = data[i]
        entry2 = data[i + 1]
        if entry1[0] < 0 \
                and entry1[1] > 0 \
                and entry1[2] > 0 \
                and entry2[1] > 0 \
                and entry2[2] > 0 \
                and calculate_distance(0, 0, entry1[1], entry1[2]) <= total_distance \
                and calculate_distance(0, 0, entry2[1], entry2[2]) <= total_distance:
            times += calculate_distance(entry1[1], entry1[2], entry2[1], entry2[2]) / calculate_v(9.81, -entry1[0])
        else:
            #Invalid height
            if entry1[0] >= 0:
                invalidheights += 1

            #Invalid coords
            if     entry1[1] <= 0 \
                or entry1[2] <= 0 \
                or entry2[1] <= 0 \
                or entry2[2] <= 0:
                    invalidcoords += 1

            #Invalid distance
            if calculate_distance(0, 0, entry1[1], entry1[2]) > total_distance \
                or calculate_distance(0, 0, entry2[1], entry2[2]) > total_distance:
                invaliddistance += 1

            #Add to general counter
            entriesSkipped += 1

    #Print statistics
    print("\n-- Statistics --")
    print "Total entries " + str(len(data))
    print "Entries skipped "  + str(entriesSkipped)
    print "\tInvalid height " + str(invalidheights)
    print "\tInvalid coords " + str(invalidcoords)
    print "\tInvalid distance " + str(invaliddistance)

    return times


distance_to_soma = calculate_distance(0, 0, 54600, 127600)

print "Distance to soma: " + str(distance_to_soma/1000) + " km"
print("Calculated arrival time: "
      + str(calculate_travel_time(readfile('soma_epicenter_tohoku_2011_bathymetry.csv'),
                                  distance_to_soma)) + " seconds")
