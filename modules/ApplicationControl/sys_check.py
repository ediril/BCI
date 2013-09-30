'''
System check: would perform and report on a suite of inter-dependent tests of
 the system.

tests
-----
message_manager
quick_logger

spm_module <- message_manager
cerebus_connected <- spm_module
cerebus_heartbeats <- cerebus_connected
cerebus_count_packets <- cerebus_connected

spm_counts <- cerebus_heartbeats, cerebus_count_packets, spm_module
combo_module <- message_manager
spike_combos <- combo_module, (spm_counts)

em_module <- message_manager
em_commands <- em_module, (spike_combos)

mpl_module <- message_manager
mpl_connected <- mpl_module
mpl_moves <- mpl_connected, (em_commands)
mpl_output <- mpl_connected, (em_commands)

denso_module <- message_manager
denso_connected <- denso_module
denso_moves <- denso_connected

joystick_module <- message_manager
joystick_connected <- joystick_module
joystick_commands <- joystick_connected

viz_module <- message_manager
analog_module <- message_manager
silicon_dog_module <- message_manager

'''
from subprocess import Popen

class RP3Test(object):
    dependencies = []
    name = "RP3Test"

    def deps_met(self):
        if not (False in self.dependencies):
            print "%s: Test passed" % (self.name)
            return True

    def run(self):
        if self.deps_met():
            # test stuff
            return self.test()
        else:
            # dependencies not met
            return False

    def test(self):
        return True
    
class MessageManagerTest(RP3Test):
    name = "MessageManagerTest"

    def test(self):
        pass
    
tests = [RP3Test(),
         MessageManagerTest()]

for test in tests:
    test.run()
