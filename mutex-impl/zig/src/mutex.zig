const std = @import("std");
const atomic = std.atomic;

pub const Mutex = struct {
    locked: atomic.Value(bool) = atomic.Value(bool).init(false),
    owner: std.Thread.Id = undefined,

    pub fn lock(self: *Mutex) void {
        while (self.locked.swap(true, .acquire)) {
            // spin
            atomic.spinLoopHint();
        }
        self.owner = std.Thread.getCurrentId();
    }

    pub fn unlock(self: *Mutex) void {
        if (self.owner != std.Thread.getCurrentId()) {
            std.debug.panic("unlocking mutex not owned by current thread", .{});
        }
        self.owner = undefined;
        self.locked.store(false, .release);
    }
};
