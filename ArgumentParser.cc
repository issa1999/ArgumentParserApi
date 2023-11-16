#include "Options.hh"
using namespace std;
Option::Option() {
    _haveMultipleValues = false;
    _optionName = "";
    _type = NONE;
    _isMandatory = false;
    _description = "This is an empty option used to declare that there is an error while getting an option";
    _value = {-1, ''};

}
Option::Option(Option& option) {
    _haveMultipleValues = option.haveMultipleValues();
    _optionName = option.getOptionName();
    _type = option.getType();
    _isMandatory = option.isMandatory();
    _description = option.getHelp();
    _value = option.getValue();
}
void Options::addNewOption(Tools, Option option) {
    if (canAddOption(option)) {
        _Options.insert({_Options.size()-1, option});
    } else {
        exit(1);
    }
}

bool Options::matchesTool(Option option, Tools tool) {
    auto toolOptions = _ToolsOptions.find(tool);
    if (toolOptions == _ToolsOptions.end()) {
        return false;
    }
    Option foundOption = toolOptions->second.getOption(option);
    if (foundOption.getType() == Option::OptionType::NONE) return false;
    return true;
}

bool canAddOption()