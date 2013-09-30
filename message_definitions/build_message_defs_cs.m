dragonfly_path = getenv('DRAGONFLY');
addpath( [dragonfly_path '/tools/']);
bci_path = getenv('BCI_INCLUDE');
addpath( bci_path);
build_dotNet_message_defs([ bci_path '/Dragonfly_config.h']);