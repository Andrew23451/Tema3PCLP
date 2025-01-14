import os
import subprocess
import tempfile

def dispatch_helper():
    link_helper = subprocess.run(['make', 'dispatch_helper'], capture_output=True, text=True)
    if link_helper.returncode != 0:
        print('Fatal error. Failed to link correct helper object. Exiting...')
        exit(-1)

def check_task_1_1():
    dispatch_helper()
    os.system("gcc checker/checker.c checker/helper.o src/task1.c src/task3.c -o checker.exe -Iinclude -lm")
    os.system("chmod +x checker.exe") 
    result = subprocess.run(['./checker.exe', '1'], capture_output=True, text=True)  
    print(result.stdout)
    return result.returncode

def check_task_1_2():
    dispatch_helper()
    os.system("gcc checker/checker.c checker/helper.o src/task1.c src/task3.c -o checker.exe -Iinclude -lm")
    os.system("chmod +x checker.exe") 
    result = subprocess.run(['./checker.exe', '2'], capture_output=True, text=True)  
    print(result.stdout)
    return result.returncode

def check_task_1_3():
    dispatch_helper()
    os.system("gcc checker/checker.c checker/helper.o src/task1.c src/task3.c -o checker.exe -Iinclude -lm")
    os.system("chmod +x checker.exe") 
    
    result = subprocess.run(['./checker.exe', '3'], capture_output=True, text=True)
    if result.returncode != 5:
        print(result.stdout)
        return 0
    
    result = subprocess.run(['valgrind', '--leak-check=full', './checker.exe', '3'], capture_output=True, text=True)
    if "ERROR SUMMARY: 0 errors from 0 contexts" in result.stderr:
        print("Task 1.3 trecut cu succes!")
        return 5
    else:
        print("Memory leaks found")
        print(result.stderr)
    return 0

def check_task_1():
    points = 0
    print("TASK 1")
    print("----------------")
    print("Verificare task 1.1")
    points += int(check_task_1_1())
    print("----------------")
    print("Verificare task 1.2")
    points += int(check_task_1_2())
    print("----------------")
    print("Verificare task 1.3")
    points += int(check_task_1_3())
    print("----------------")
    print("Numarul total de puncte: " + str(points))

    os.system("rm checker.exe")
    return points

def check_task_2():
    dispatch_helper()
    result_make = subprocess.run(['make', 'build'], capture_output=True, text=True)
    if result_make.returncode != 0:
        print("Eroare la compilare!")
        print(result_make.stderr)
        return 0
    
    points = 0
    valgrind_pass = True
    os.system("chmod +x tema3")

    print("TASK 2")
    print("----------------")

    for database in os.listdir("tests/db"):
        if not os.path.isfile(os.path.join("tests/db", database)):
            continue
        print("Database: " + database)
        print()
        for test in os.listdir("tests/input"):
            print("Test: " + test)

            input_test = "tests/input/" + test
            output_test = "tests/output/" + database.split(".")[0] + "." + test.split(".")[0] + ".out"
            ref_test = "tests/ref/" + database.split(".")[0] + "." + test.split(".")[0] + ".ref"

            with open(input_test, 'r') as f:
                result = subprocess.run(['./tema3', 'tests/db/' + database], stdin=f, capture_output=True, text=True)
            
            if result.returncode != 0:
                print("Eroare de rulare! Posibil segmentation fault.")
                continue

            with open(output_test, 'w') as f:
                f.write(result.stdout)
            
            if (os.system(f"diff {output_test} {ref_test} > /dev/null") != 0):
                print("Rezultat incorect!")
            
            else:
                print(f"{test} - OK")
                points += 3.5
                valgrind_pass &= check_valgrind("tema3", database, input_test)
            print("----------------")
    if not valgrind_pass:
        print("Depunctare pentru memory leaks. -10 puncte")
        points -= 10

    print("Numarul total de puncte: " + str(points))        
    return points

def check_task_3():
    if not os.path.exists("tests/output/task3"):
        os.makedirs("tests/output/task3")
    dispatch_helper()
    os.system("gcc checker/checker.c checker/helper.o src/task1.c src/task3.c -o checker.exe -Iinclude -lm")
    os.system("chmod +x checker.exe") 
    result = subprocess.run(['./checker.exe', '4'], capture_output=True, text=True)  
    print(result.stdout)
    
    print("TASK 3")
    print("----------------")

    points = 0
    for database in sorted(os.listdir("tests/db/task3/")):
        if not os.path.isfile(os.path.join("tests/db/task3", database)):
            continue
        print("Test: " + database)
        output_test = "tests/output/task3/" + database.split(".")[0] + ".db.enc"
        ref_test = "tests/ref/task3/" + database.split(".")[0] + ".db.enc.ref"

        if os.system(f"cmp {output_test} {ref_test}") != 0:
            print(f"{database} - Rezultat incorect!")
        else:
            print(f"{database} - OK")
            points += 5
        print("----------------")
    os.system("rm checker.exe")

    print("Numarul total de puncte: " + str(points))
    return points

def check_valgrind(exec, database, test):
    with open(test, 'r') as f:
        result = subprocess.run(['valgrind', '--leak-check=full', './' + exec, 'tests/db/' + database], stdin=f, capture_output=True, text=True)
    if "ERROR SUMMARY: 0 errors from 0 contexts" in result.stderr:
        print("Valgrind OK.")
        return True
    else:
        print("Memory leaks found")
        print(result.stderr)
    return False

def check_readme():
    print("README")
    print("----------------")
    if not os.path.exists("README.md"):
        print("README.md lipseste! -5 puncte")
        return -5
    return 0

def print_result(test_name, result):
    print(f"{test_name}: {result}")

def check_coding_style():
    is_style_ok = True
    total_score = 0
    print("CODING STYLE")
    print("----------------")
    with tempfile.NamedTemporaryFile(delete=False, mode='w+', encoding='utf-8') as result_temp:
        temp_file_path = result_temp.name
        if os.path.isdir('.venv'):
            activate_script = os.path.join('.venv', 'bin', 'activate')
            subprocess.run(['source', activate_script], shell=True, check=False)

        result_temp.write("\nRun cpplint\n\n")
        try:
            cpplint_command = [
                "cpplint",
                "--filter=-legal/copyright,-readability/casting,-build/include_subdir,-runtime/threadsafe_fn,-build/header_guard,-runtime/int,-build/include_what_you_use",
                "--linelength=120",
                *subprocess.getoutput("find ./src/ -name '*.c'").splitlines()
            ]
            cpplint_result = subprocess.run(cpplint_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            result_temp.write(cpplint_result.stderr)

            if cpplint_result.returncode != 0:
                is_style_ok = False
        except Exception as e:
            result_temp.write(f"Error running cpplint: {str(e)}\n")
            is_style_ok = False

        if os.path.isdir('.venv'):
            subprocess.run(['deactivate'], shell=True, check=False)

        result_temp.write("\nRun clang-tidy\n\n")
        try:
            clang_tidy_command = [
                "clang-tidy",
                "-checks=-*,cppcoreguidelines*,-cppcoreguidelines-macro-to-enum",
                "--warnings-as-errors=-*,cppcoreguidelines*,-cppcoreguidelines-macro-to-enum",
                *subprocess.getoutput("find ./src -name '*.h' -or -name '*.c'").splitlines(),
                "--"
            ]
            clang_tidy_result = subprocess.run(clang_tidy_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            result_temp.write(clang_tidy_result.stdout)
            result_temp.write(clang_tidy_result.stderr)

            if clang_tidy_result.returncode != 0:
                is_style_ok = False
        except Exception as e:
            result_temp.write(f"Error running clang-tidy: {str(e)}\n")
            is_style_ok = False

    if not is_style_ok:
        print_result("Test Coding Style", "-20/0p failed")
        total_score = -20
    else:
        print_result("Test Coding Style", "0/0p passed")

    try:
        subprocess.run(['awk', '-f', 'checker/parse.awk', temp_file_path], check=False)
    except Exception as e:
        print(f"Error running summary parsing: {str(e)}")

    print("\n================================")
    print("= Detailed coding style report =")
    print("================================\n")
    with open(temp_file_path, 'r', encoding='utf-8') as result_temp:
        print(result_temp.read())

    os.remove(temp_file_path)
    return total_score

def main():
    points = 0
    points += check_task_1()
    print()
    points += check_task_2()
    print()
    points += check_task_3()
    print()
    points += check_readme()
    print()
    points += check_coding_style()
    print()
    print("PUNCTAJ FINAL: " + str(points))
    os.system("rm -f tema3")

if __name__ == "__main__":
    main()