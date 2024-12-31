type_dirs = ["8_i", "16_565", "16_5551_rgb", "16_5551_rgba", "24_tc", "32_tc_rgb", "32_tc_rgba", "raw_examples"]
operations = ["hflip", "vflip", "grayscale"]
files = ["france.bmp", "greenblue_square.bmp", "handcrafted.bmp"]

for dir in type_dirs:
    for operation in operations:
        for file in files:
            cmd = f"cat ./bmp_examples/{dir}/raw/{file} | ./imageprocessor {operation.upper()} > ./bmp_examples/{dir}/{operation}/{file}"
            print(cmd)