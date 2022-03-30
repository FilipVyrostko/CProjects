import os

def main():

    IPv4 = readIPv4()
    IPv6 = readIPv6()

    writeIPv4(IPv4)
    writeIPv6(IPv6)

    return 0


def readIPv4():
    with open("IPv4.txt", "r") as f:
        lines = f.readlines()
        IPv4 = []
        l = []
        for line in lines:
            if not line.startswith("traceroute"):
                line = line.replace("\n", "")

                ip = [i for i in line.split(" ") if i != ""][1]
                if ip != "*" and ip != "to":
                    l.append(ip)
            else:
                if l:
                    IPv4.append(l)
                l = []


    return IPv4

def readIPv6():
    with open("IPv6.txt", "r") as f:
        lines = f.readlines()
        IPv6 = []
        l = []
        for line in lines:
            if not line.startswith("traceroute"):
                line = line.replace("\n", "")

                ip = [i for i in line.split(" ") if i != ""][1]
                if ip != "*" and ip != "to":
                    l.append(ip)
            else:
                if l:
                    IPv6.append(l)
                l = []

    return IPv6

def writeIPv4(IPv4):

    for ipList in IPv4:
        with open("ipv4.dot", "a") as f:
            
            for i in range(len(ipList)-1):
                f.write("\""+ipList[i]+"\""+"--"+"\""+ipList[i+1]+"\""+"\n")
        
    os.system("cat ipv4.dot | sort | uniq > router-topology-v4.dot")
    os.system("rm ipv4.dot")

    content = []

    with open("router-topology-v4.dot", "r") as f:
        content = f.readlines()

    with open("router-topology-v4.dot", "w") as f:
        f.write("graph routertopology {\n")
        for line in content:
            f.write(line)
        f.write("}")

    os.system("dot -T pdf -o router-topology-v4.pdf router-topology-v4.dot")

def writeIPv6(IPv6):

    for ipList in IPv6:
        with open("ipv6.dot", "a") as f:
            
            for i in range(len(ipList)-1):
                f.write("\""+ipList[i]+"\""+"--"+"\""+ipList[i+1]+"\""+"\n")

    os.system("cat ipv6.dot | sort | uniq > router-topology-v6.dot")
    os.system("rm ipv6.dot")

    content = []

    with open("router-topology-v6.dot", "r") as f:
        content = f.readlines()

    with open("router-topology-v6.dot", "w") as f:
        f.write("graph routertopology {\n")
        for line in content:
            f.write(line)
        f.write("}")

    os.system("dot -T pdf -o router-topology-v6.pdf router-topology-v6.dot")


if __name__ == "__main__":
    main()



