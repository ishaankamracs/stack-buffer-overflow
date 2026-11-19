# Stack Buffer Overflows

COMP 211, Checkoff 3. Ishaan Kamra.

## The topic

In C, if you write past the end of an array, nothing stops you. The extra data just lands on whatever is stored next to the array. For a local array, that's the rest of the function's stack frame, like other variables or the return address.

That's a stack buffer overflow. It sounds like a small mistake, but bugs like it have caused real hacks. In 2019, WhatsApp users could get hacked by a call they never even picked up.

## My example

```c
void login(int64_t n) {
    int64_t access = 0;
    int64_t pin[2];
    for (int64_t i = 0; i < n; i++)
        pin[i] = 9;
    if (access != 0) printf("Access granted\n");
}
```

`pin` only has room for 2 numbers. If `main` calls `login(3)`, the loop writes a third one, and `pin[2]` lands right where `access` is stored:

| Address | Contents | Variable |
|---|---|---|
| 0xFFFFAAAA0040 | 0 | main: RA |
| 0xFFFFAAAA0038 | 3 | login: n |
| 0xFFFFAAAA0030 | 2 | login: RA |
| 0xFFFFAAAA0028 | ~~0~~ 9 | login: access |
| 0xFFFFAAAA0020 | 9 | login: pin[1] |
| 0xFFFFAAAA0018 | 9 | login: pin[0] |
| 0xFFFFAAAA0010 | ~~0 1 2~~ 3 | login: i |

`access` was supposed to stay 0, but now it's 9, so the program prints "Access granted."

The lock is obviously fake, but the mistake is real: copying data without checking that it fits.

## What I learned

**C doesn't check.** `pin[2]` doesn't exist, but C still figures out where it would be and writes there.

**It doesn't crash.** `login(3)` just grants access and finishes normally, so you wouldn't even know something went wrong.

**My laptop didn't match the textbook.** In the class diagram, a bigger overflow like `login(4)` would hit the return address and crash. When I ran it, it didn't crash until `login(16)`. I found out my Mac uses an ARM chip, which stores the return address in a different spot, below the array, so the overflow can't reach it as easily.

**There's a safety check.** If you compile normally, the program catches the overflow and stops with "stack smashing detected." I had to turn that check off to make the demo work.

## How to run it

Inside the course's Docker container:

```
cd code
make
./login 2      # Access denied
./login 3      # Access granted
```

`./login_addresses 3` also prints where `pin` and `access` are in memory, so you can see that `pin[2]` and `access` are the same spot.

## Slides

In `slides/`.

## References

- Check Point Research, "The NSO WhatsApp Vulnerability: This is How It Happened" (2019): https://research.checkpoint.com/2019/the-nso-whatsapp-vulnerability-this-is-how-it-happened/
- CrowdStrike, Root Cause Analysis, Channel File 291 (2024): https://crowdstrike.com/wp-content/uploads/2024/08/Executive-Summary_Root-Cause-Analysis_Channel-File-291.pdf
- The White House, Memory Safety Fact Sheet (2024): https://bidenwhitehouse.archives.gov/oncd/briefing-room/2024/02/26/memory-safety-fact-sheet
- COMP 211 notes on stack memory diagrams
- My conversation with Claude while exploring the topic: https://claude.ai/share/849feba9-9537-4eef-b12b-4309d22e8201
