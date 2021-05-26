import ast
import re
import numpy as np
import matplotlib.pyplot as plt

# to actually run the profiling, use something like:
# for i in {1..10}; do _=$(cat ../test/write_testcase.txt | /usr/bin/time -o ./pypy.profiling.txt --append -f "%e real,\t%U user,\t%S sys,\t%P CPU,\t%Mk max mem,\t%F major pagefaults,\t%R minor pagefaults" pypy3 client.py); done

REGEX = '^(?P<real>\d+\.\d+) real,	(?P<user>\d+\.\d+) user,	(?P<sys>\d+\.\d+) sys,	(?P<cpu>\d+)% CPU,	(?P<maxmem>\d+)k max mem,	(?P<Mpagefaults>\d+) major pagefaults,	(?P<mpagefaults>\d+) minor pagefaults'
regex = re.compile(REGEX)
groups = list(regex.groupindex)

time_dict = {"real":0, "user":0, "sys":0}
mem_dict = {"maxmem" :0, "Mpagefaults":0, "mpagefaults":0}
cpu_dict = {"cpu":0}

time_profile_dict = {
    "cpp":time_dict.copy(),
    "cpython":time_dict.copy(),
    "pypy":time_dict.copy(),
}
mem_profile_dict = {
    "cpp":mem_dict.copy(),
    "cpython":mem_dict.copy(),
    "pypy":mem_dict.copy(),
}
cpu_profile_dict = {
    "cpp": cpu_dict.copy(),
    "cpython": cpu_dict.copy(),
    "pypy": cpu_dict.copy()
}

write_profiles = {"time": time_profile_dict.copy(),"mem":mem_profile_dict.copy(), "cpu": cpu_profile_dict.copy()}
read_profiles = {"time": time_profile_dict.copy(),"mem":mem_profile_dict.copy(), "cpu": cpu_profile_dict.copy()}
delete_profiles = {"time": time_profile_dict.copy(),"mem":mem_profile_dict.copy(), "cpu": cpu_profile_dict.copy()}

def make_time_plot(profile_dict, profile_type):
    # set width of bars
    barWidth = 0.10

    # set heights of bars
    bars1 = [profile_dict["time"]["cpp"]["sys"], profile_dict["time"]["cpp"]["user"]]
    bars2 = [profile_dict["time"]["pypy"]["sys"],profile_dict["time"]["pypy"]["user"]]
    bars3 = [profile_dict["time"]["cpython"]["sys"],profile_dict["time"]["cpython"]["user"]]

    # Set position of bar on X axis
    r1 = np.arange(len(bars1))
    r2 = [x + barWidth for x in r1]
    r3 = [x + barWidth for x in r2]

    # Make the plot
    plt.bar(r1, bars1, color = "sandybrown", width=barWidth, edgecolor='white', label='CPP')
    plt.bar(r2, bars2, color = "lightseagreen", width=barWidth, edgecolor='white', label='PyPy')
    plt.bar(r3, bars3, color = "plum", width=barWidth, edgecolor='white', label='CPython')

    # Add xticks on the middle of the group bars
    plt.xlabel('Time of {0} Query'.format(profile_type), fontweight='bold')
    plt.xticks([r + barWidth for r in range(len(bars1))], ['System', 'User'])
    
    # Create legend & Show graphic
    plt.legend()
    plt.show()


def make_real_time_plot(read_profile, write_profile, delete_profile):
    # set width of bars
    barWidth = 0.15
 
    # set heights of bars    
    bars1 = [read_profile["time"]["cpp"]["real"], write_profile["time"]["cpp"]["real"],delete_profile["time"]["cpp"]["real"]]
    bars2 = [read_profile["time"]["pypy"]["real"],write_profile["time"]["pypy"]["real"], delete_profile["time"]["pypy"]["real"]]
    bars3 = [read_profile["time"]["cpython"]["real"],write_profile["time"]["cpython"]["real"], delete_profile["time"]["cpython"]["real"]]
    
    # Set position of bar on X axis
    r1 = np.arange(len(bars1))
    r2 = [x + barWidth for x in r1]
    r3 = [x + barWidth for x in r2]

    # Make the plot
    plt.bar(r1, bars1, color= "sandybrown", width=barWidth, edgecolor='white', label='CPP')
    plt.bar(r2, bars2, color="lightseagreen", width=barWidth, edgecolor='white', label='PyPy')
    plt.bar(r3, bars3, color= "plum", width=barWidth, edgecolor='white', label='CPython')

    # Add xticks on the middle of the group bars
    x_label = "Real time"
   
    plt.xlabel(x_label, fontweight='bold')
    plt.xticks([r + barWidth for r in range(len(bars1))], ['Read', 'Write', 'Delete'])
    
    # Create legend & Show graphic
    plt.legend()
    plt.show()



def make_mem_plot(read_profile, write_profile, delete_profile, memory_info):
    # set width of bars
    barWidth = 0.15

    # set heights of bars    
    bars1 = [read_profile["mem"]["cpp"][memory_info], write_profile["mem"]["cpp"][memory_info],delete_profile["mem"]["cpp"][memory_info]]
    bars2 = [read_profile["mem"]["pypy"][memory_info],write_profile["mem"]["pypy"][memory_info], delete_profile["mem"]["pypy"][memory_info]]
    bars3 = [read_profile["mem"]["cpython"][memory_info],write_profile["mem"]["cpython"][memory_info], delete_profile["mem"]["cpython"][memory_info]]
    
    # Set position of bar on X axis
    r1 = np.arange(len(bars1))
    r2 = [x + barWidth for x in r1]
    r3 = [x + barWidth for x in r2]

    # Make the plot
    plt.bar(r1, bars1, color= "sandybrown", width=barWidth, edgecolor='white', label='CPP')
    plt.bar(r2, bars2, color="lightseagreen", width=barWidth, edgecolor='white', label='PyPy')
    plt.bar(r3, bars3, color= "plum", width=barWidth, edgecolor='white', label='CPython')


    # Add xticks on the middle of the group bars
    x_label = "Max Memory Usage"
    if memory_info == "mpagefaults":
        x_label = "Minor pagefaults"
    plt.xlabel(x_label, fontweight='bold')
    plt.xticks([r + barWidth for r in range(len(bars1))], ['Read', 'Write', 'Delete'])
    
    # Create legend & Show graphic
    plt.legend()
    plt.show()

def make_cpu_plot(read_profile, write_profile, delete_profile, cpu_info="cpu"):
    # set width of bars
    barWidth = 0.15

    # set heights of bars
    # bars1 = [read_profile["cpu"]["cpp"][cpu_info], read_profile["cpu"]["cpython"][cpu_info], read_profile["cpu"]["pypy"][cpu_info]]
    # bars2 = [write_profile["cpu"]["cpp"][cpu_info], write_profile["cpu"]["cpython"][cpu_info], write_profile["cpu"]["pypy"][cpu_info]]
    # bars3 = [delete_profile["cpu"]["cpp"][cpu_info], delete_profile["cpu"]["cpython"][cpu_info], delete_profile["cpu"]["pypy"][cpu_info]]

    bars1 = [read_profile["cpu"]["cpp"][cpu_info], write_profile["cpu"]["cpp"][cpu_info],delete_profile["cpu"]["cpp"][cpu_info]]
    bars2 = [read_profile["cpu"]["pypy"][cpu_info],write_profile["cpu"]["pypy"][cpu_info], delete_profile["cpu"]["pypy"][cpu_info]]
    bars3 = [read_profile["cpu"]["cpython"][cpu_info],write_profile["cpu"]["cpython"][cpu_info], delete_profile["cpu"]["cpython"][cpu_info]]

    # Set position of bar on X axis
    r1 = np.arange(len(bars1))
    r2 = [x + barWidth for x in r1]
    r3 = [x + barWidth for x in r2]

    # Make the plot
    plt.bar(r1, bars1, color= "sandybrown", width=barWidth, edgecolor='white', label='CPP')
    plt.bar(r2, bars2, color="lightseagreen", width=barWidth, edgecolor='white', label='PyPy')
    plt.bar(r3, bars3, color= "plum", width=barWidth, edgecolor='white', label='CPython')

    # Add xticks on the middle of the group bars
    plt.xlabel("CPU Usage", fontweight='bold')
    plt.xticks([r + barWidth for r in range(len(bars1))], ['Read', 'Write', 'Delete'])
    
    # Create legend & Show graphic
    plt.legend()
    plt.show()

def get_runtime_type(filename):
    runtime_type = "pypy"
    if "cpp" in filename:
        runtime_type = "cpp"
    elif "cpython" in filename:
        runtime_type = "cpython"
    
    return runtime_type


def parse_profile(filename):
    print('-'*20+f'\n{filename}\n'+'-'*20)
    with open(filename, 'r') as f:
        total = {group:0 for group in groups}
        lines = f.readlines()
        for line in lines:
            match = regex.match(line)
            for group in groups:
                total[group] += ast.literal_eval(match.group(group))
        
        runtime = get_runtime_type(filename)

        #print({k:round(v/len(lines),2) for k,v in total.items()})
        for k,v in total.items():
            v = round(v/len(lines),2)
            print(k," : " ,v)            
            if "write" in filename:
                if k in time_dict.keys() and write_profiles["time"][runtime][k] == 0:
                    write_profiles["time"][runtime][k] = v
                elif k in mem_dict.keys() and write_profiles["mem"][runtime][k] == 0:
                    write_profiles["mem"][runtime][k]= v
                elif k in cpu_dict.keys():
                    write_profiles["cpu"][runtime][k]= v

            elif "read" in filename:
                if k in time_dict.keys() and read_profiles["time"][runtime][k] == 0:
                    read_profiles["time"][runtime][k] = v
                elif k in mem_dict.keys() and read_profiles["mem"][runtime][k] == 0:
                    read_profiles["mem"][runtime][k]= v
                elif k in cpu_dict.keys():
                    read_profiles["cpu"][runtime][k]= v

            elif "delete" in filename:
                if k in time_dict.keys() and delete_profiles["time"][runtime][k] == 0:
                    delete_profiles["time"][runtime][k] = v
                elif k in mem_dict.keys() and delete_profiles["mem"][runtime][k] == 0:
                    delete_profiles["mem"][runtime][k]= v
                elif k in cpu_dict.keys():
                    delete_profiles["cpu"][runtime][k]= v


for filename in ['profiling_data/cpp.write.profile', 'profiling_data/cpython.write.profile', 'profiling_data/pypy.write.profile',
                 'profiling_data/cpp.read.profile', 'profiling_data/cpython.read.profile', 'profiling_data/pypy.read.profile',
                 'profiling_data/cpp.delete.profile', 'profiling_data/cpython.delete.profile', 'profiling_data/pypy.delete.profile']:
    parse_profile(filename)

make_time_plot(write_profiles, profile_type="Write")
# make_time_plot(read_profiles, profile_type="Read")
# make_time_plot(delete_profiles, profile_type="Delete")

make_real_time_plot(read_profiles, write_profiles, delete_profiles)

make_mem_plot(read_profiles, write_profiles, delete_profiles, memory_info="maxmem")

make_mem_plot(read_profiles, write_profiles, delete_profiles, memory_info="mpagefaults")

make_cpu_plot(read_profiles, write_profiles, delete_profiles)