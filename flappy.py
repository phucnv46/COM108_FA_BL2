import curses
import time
import random

GRAVITY = 0.3       # per frame (slower fall)
FLAP_VEL = -3.8     # reduced flap strength
PIPE_SPEED = 0.5    # columns per frame (slower scroll)
FLAP_COOLDOWN_S = 0.12  # minimum time between flaps (seconds)
PIPE_SPACING = 28   # columns between pipes
MIN_GAP = 5         # minimum gap size
MAX_GAP = 9         # maximum gap size
BIRD_CHAR = '>@'
PIPE_CHAR = '#'


def clamp(val, lo, hi):
    return max(lo, min(hi, val))


def draw_text(stdscr, y, x, text, attr=0):
    h, w = stdscr.getmaxyx()
    if 0 <= y < h and 0 <= x < w:
        try:
            stdscr.addnstr(y, x, text, max(0, w - x), attr)
        except curses.error:
            pass


def main(stdscr):
    curses.curs_set(0)
    stdscr.nodelay(True)
    stdscr.timeout(0)
    curses.noecho()
    curses.cbreak()
    try:
        if curses.has_colors():
            curses.start_color()
            curses.init_pair(1, curses.COLOR_YELLOW, curses.COLOR_BLACK)  # bird
            curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)   # pipes
            curses.init_pair(3, curses.COLOR_CYAN, curses.COLOR_BLACK)    # info
            bird_attr = curses.color_pair(1)
            pipe_attr = curses.color_pair(2)
            info_attr = curses.color_pair(3)
        else:
            bird_attr = pipe_attr = info_attr = 0

        def reset():
            h, w = stdscr.getmaxyx()
            # enforce minimal playfield
            min_w, min_h = 40, 20
            w = max(w, min_w)
            h = max(h, min_h)

            bird_x = w // 4
            bird_y = float(h // 2)
            bird_v = 0.0

            pipes = []
            # seed a couple initial pipes to the right
            start_x = w + 10
            for i in range(2):
                gap = random.randint(MIN_GAP, MAX_GAP)
                gap_center = random.randint(4 + gap // 2, h - 5 - gap // 2)
                pipes.append({
                    'x': float(start_x + i * PIPE_SPACING),
                    'gap_center': gap_center,
                    'gap': gap,
                    'scored': False,
                })

            score = 0
            paused = False
            alive = True
            return {
                'h': h, 'w': w,
                'bird_x': bird_x, 'bird_y': bird_y, 'bird_v': bird_v,
                'pipes': pipes, 'score': score,
                'paused': paused, 'alive': alive,
                'frames': 0,
                'flap_cd': 0  # frames until next allowed flap
            }

        state = reset()
        last_spawn_x = state['pipes'][-1]['x'] if state['pipes'] else 0.0

        def spawn_pipe(next_x):
            h = state['h']
            # dynamic gap: shrinks a bit with score, but not below MIN_GAP
            gap = clamp(MAX_GAP - state['score'] // 10, MIN_GAP, MAX_GAP)
            gap_center = random.randint(4 + gap // 2, h - 5 - gap // 2)
            return {'x': float(next_x), 'gap_center': gap_center, 'gap': gap, 'scored': False}

        # game loop
        fps = 30.0
        delay = 1.0 / fps
        flap_cd_frames = max(1, int(fps * FLAP_COOLDOWN_S))

        while True:
            start_t = time.perf_counter()

            # Read a few inputs if queued
            key = stdscr.getch()
            while key != -1:
                if key in (ord('q'), ord('Q')):
                    return
                if key in (ord('p'), ord('P')):
                    state['paused'] = not state['paused']
                if key in (curses.KEY_UP, ord(' '), ord('w'), ord('W')):
                    if state['alive'] and state['flap_cd'] == 0:
                        state['bird_v'] = FLAP_VEL
                        state['flap_cd'] = flap_cd_frames
                    else:
                        # dead or in cooldown; ignore flap
                        pass
                if not state['alive'] and key in (ord('r'), ord('R')):
                    state = reset()
                    last_spawn_x = state['pipes'][-1]['x'] if state['pipes'] else 0.0
                key = stdscr.getch()

            # Update window size (handle resize)
            h, w = stdscr.getmaxyx()
            if h != state['h'] or w != state['w']:
                # on resize, re-center a bit but keep progress
                state['h'], state['w'] = h, w
                state['bird_x'] = clamp(state['bird_x'], 2, max(2, w - 3))
                state['bird_y'] = clamp(state['bird_y'], 1, max(1, h - 2))

            # Update
            if not state['paused'] and state['alive']:
                state['frames'] += 1

                # Decrease flap cooldown
                if state['flap_cd'] > 0:
                    state['flap_cd'] -= 1

                # Bird physics
                state['bird_v'] += GRAVITY
                state['bird_v'] = clamp(state['bird_v'], -12.0, 12.0)
                state['bird_y'] += state['bird_v']

                # World bounds
                if state['bird_y'] < 1 or state['bird_y'] > state['h'] - 2:
                    state['alive'] = False

                # Move pipes
                for p in state['pipes']:
                    p['x'] -= PIPE_SPEED

                # Spawn new pipes
                if not state['pipes']:
                    next_x = state['w'] + PIPE_SPACING
                    state['pipes'].append(spawn_pipe(next_x))
                    last_spawn_x = next_x
                else:
                    rightmost = max(p['x'] for p in state['pipes'])
                    if rightmost < state['w'] - PIPE_SPACING + 1:
                        next_x = max(last_spawn_x + PIPE_SPACING, state['w'])
                        state['pipes'].append(spawn_pipe(next_x))
                        last_spawn_x = next_x

                # Remove off-screen pipes
                state['pipes'] = [p for p in state['pipes'] if p['x'] > -2]

                # Collision + score
                bird_x = state['bird_x']
                by = int(round(state['bird_y']))
                for p in state['pipes']:
                    px = int(round(p['x']))
                    gap_top = p['gap_center'] - p['gap'] // 2
                    gap_bot = p['gap_center'] + p['gap'] // 2
                    # Score when pipe passes bird
                    if not p['scored'] and px + 1 < bird_x:
                        p['scored'] = True
                        state['score'] += 1
                    # Collision when at column of pipe
                    if px == bird_x:
                        if not (gap_top <= by <= gap_bot):
                            state['alive'] = False

            # Draw
            stdscr.erase()

            # Border
            try:
                stdscr.border()
            except curses.error:
                pass

            # Draw pipes
            for p in state['pipes']:
                px = int(round(p['x']))
                if 1 <= px < state['w'] - 1:
                    gap_top = p['gap_center'] - p['gap'] // 2
                    gap_bot = p['gap_center'] + p['gap'] // 2
                    for y in range(1, state['h'] - 1):
                        if not (gap_top <= y <= gap_bot):
                            try:
                                stdscr.addch(y, px, PIPE_CHAR, pipe_attr)
                            except curses.error:
                                pass

            # Draw bird
            by = int(round(state['bird_y']))
            bx = state['bird_x']
            if 1 <= by < state['h'] - 1 and 1 <= bx < state['w'] - 1:
                draw_text(stdscr, by, bx, BIRD_CHAR, bird_attr)

            # UI
            draw_text(stdscr, 0, 2, f" Score: {state['score']} ", info_attr)
            draw_text(stdscr, 0, state['w'] - 28, " [Space/Up] Flap  P Pause  Q Quit ", info_attr)

            if state['paused']:
                msg = " PAUSED - press P to resume "
                draw_text(stdscr, state['h'] // 2, (state['w'] - len(msg)) // 2, msg, info_attr)

            if not state['alive']:
                msg1 = " GAME OVER "
                msg2 = " Press R to restart or Q to quit "
                draw_text(stdscr, state['h'] // 2 - 1, (state['w'] - len(msg1)) // 2, msg1, info_attr)
                draw_text(stdscr, state['h'] // 2 + 1, (state['w'] - len(msg2)) // 2, msg2, info_attr)

            stdscr.refresh()

            # Frame pacing
            elapsed = time.perf_counter() - start_t
            to_sleep = delay - elapsed
            if to_sleep > 0:
                time.sleep(to_sleep)

    finally:
        # restore terminal modes on exit
        curses.nocbreak()
        stdscr.keypad(False)
        curses.echo()
        curses.endwin()


if __name__ == "__main__":
    curses.wrapper(main)
