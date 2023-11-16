#include<pair>
#include <map>
#include<string>
static enum Tools {VELPREP, VELPOST, OTHER};
class Option {
    public:
    Option() ;
    Option(Option&);
    //enum OptionStatus {MANDATORY, OPTIONAL};
    enum OptionType {BOOLEAN, STRING, NUMBER, REAL, OTHER, NONE};
    void supportMultipleValues() {_haveMultipleValues = true;}
    bool haveMultipleValues() {return _haveMultipleValues;  }
    const std::string& getOptionName() {return _optionName;}
    OptionType getType() {return _type;}
    bool isMandatory() { return _isMandatory;}
    void setOptionValue(int index, char*  value) {_value.insert(make_pair<int, char*>(index, value));}
    const std::string& getHelp() { return _description;}
    std::map<int, char*> getValue() {return _value;}

    friend bool operator==(const Option& l, const Option& r);
    private:
    bool _haveMultipleValues;
    std::string _optionName;
    std::map<int, char*> _value;
    OptionType _type;
    bool _isMandatory;
    std::string _description;
};
const Option NullOption();
class Options {
    friend Option;
    public:
    int computeOptions(int argc);
    static bool matchesTool(Option option, Tools tool);
    bool canAddOption(Tools tool, Option option);
    void addNewOption(Tools tool, Option option);
    void registerCommand(
        Option::OptionType type,
        const std::string& name,
        bool multipleValues,
        bool isMandatory,
        std::string description,
        Tools tool
    );
    void displayHelp(std::string tool);

    private:
    std::map<int, Option> _Options;
    static std::map<Tools, Options> _ToolsOptions;
};
class ArgumentParser {
    friend Option;
    friend Options;
    public:
    void setTool(Tools tool) {_tool = tool;}
    Tools getTool() {return _tool;}
    computeOptions(int argc);
    int execute(int argc, char* argv[]);
    void parseArguments(int argc, char* argv[]);
    private:
    int argv;
    char* argc[];
};