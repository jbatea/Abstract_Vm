#include "../includes/Avm.hpp"

Factory *Factory::_factory = NULL;

int     main(int ac, char **av)
{
    AbstractVm  abstractvm;

   	try {
     	abstractvm.getLexer().getArg(ac, av);
     	abstractvm.parseLexemes();
     	abstractvm.exit("End of program");
   	} catch (AbstractVmException e) {
   		abstractvm.exit(e.what());
   	}
    return 0;
}