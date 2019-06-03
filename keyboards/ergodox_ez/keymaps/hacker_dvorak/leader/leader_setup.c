LEADER_EXTERNS();

void qk_leader_start(void) {
    if (!leading) {
        leading = true;
        leader_time = timer_read();
        leader_sequence_size = 0;
        leader_sequence[0] = 0;
        leader_sequence[1] = 0;
        leader_sequence[2] = 0;
        leader_sequence[3] = 0;
        leader_sequence[4] = 0;
    }
}
