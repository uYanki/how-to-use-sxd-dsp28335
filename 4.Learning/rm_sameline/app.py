with open("in.c", 'r') as f1:
    with open("out.c", 'w+') as f2:
        ctx = set(f1.readlines())
        print(ctx)
        f2.write(''.join(ctx))
