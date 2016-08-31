/*
 * CommandFactory.cc
 *
 *  Created on: Jan 10, 2016
 *      Author: jpp
 */

#include <commands/CommandConstants.h>
#include <commands/CommandFactory.h>
#include <commands/CommandUtils.h>
#include <commands/CommentCommand.h>
#include <commands/ContinueContextCommand.h>
#include <commands/RetrievePhraseCommand.h>
#include <commands/EmptyCommand.h>
#include <commands/FileCommand.h>
#include <commands/QuitCommand.h>
#include <commands/MacroCommand.h>
#include <commands/InputPhraseCommand.h>
#include <commands/ExtractWordGroupCommand.h>
#include <commands/SearchPhraseCommand.h>
#include <commands/ContinueSearchPhraseCommand.h>
#include <commands/CopyInputPhraseToWorkingPhraseCommand.h>
#include <commands/RewardCommand.h>
#include <commands/PartialRewardCommand.h>
#include <commands/ExploitCommand.h>
#include <commands/CleanExploitCommand.h>
#include <commands/ExploitRandomCommand.h>
#include <commands/ExploitMemorizeCommand.h>
#include <commands/BestExploitCommand.h>
#include <commands/PushGoalCommand.h>
#include <commands/DropGoalCommand.h>
#include <commands/GetGoalPhraseCommand.h>
#include <commands/WorkingPhraseOutCommand.h>

struct timespec;

Annabell* CommandFactory::annabell;
Monitor* CommandFactory::monitor;
display* CommandFactory::aDisplay;
timespec* CommandFactory::clk0;
timespec* CommandFactory::clk1;

void CommandFactory::init(Annabell* annabell, Monitor* monitor, display* aDisplay, timespec* clk0, timespec* clk1) {
	CommandFactory::annabell = annabell;
	CommandFactory::monitor = monitor;
	CommandFactory::aDisplay = aDisplay;
	CommandFactory::clk0 = clk0;
	CommandFactory::clk1 = clk1;
}

void CommandFactory::execute(string input) {
	Command* c = CommandFactory::newCommand(input);
	c->execute();
	delete c;
}

Command* CommandFactory::newCommand(string input) {
	Command* newCommand;

	if (input.empty()) {
		newCommand = new EmptyCommand();

	} else if (CommandUtils::startsWith(input, COMMENT_CMD)) {
		newCommand = new CommentCommand();

	} else if (CommandUtils::startsWith(input, FILE_CMD) || CommandUtils::startsWith(input, FILE_CMD_LONG)) {
		newCommand = new FileCommand();

	} else if (CommandUtils::startsWith(input, QUIT_CMD) || CommandUtils::startsWith(input, QUIT_CMD_LONG)) {
		newCommand = new QuitCommand();

	} else if (CommandUtils::isMacroCommand(input)) {
		newCommand = new MacroCommand();

	} else if (CommandUtils::isInputPhrase(input)) {
		newCommand = new InputPhraseCommand();

	} else if (CommandUtils::startsWith(input, CONTINUE_CONTEXT_CMD)
			|| CommandUtils::startsWith(input, CONTINUE_CONTEXT_CMD_LONG)) {
		newCommand = new ContinueContextCommand();

	} else if (CommandUtils::startsWith(input, PHRASE_CMD_LONG) || CommandUtils::startsWith(input, PHRASE_CMD)) {
		newCommand = new RetrievePhraseCommand();

	} else if (CommandUtils::startsWith(input, WORD_GROUP_CMD_LONG) || CommandUtils::startsWith(input, WORD_GROUP_CMD)) {
		newCommand = new ExtractWordGroupCommand();

	} else if(CommandUtils::startsWith(input, SEARCH_CONTEXT_CMD_LONG) || CommandUtils::startsWith(input, SEARCH_CONTEXT_CMD)) {
		newCommand = new SearchPhraseCommand();

	} else if (CommandUtils::startsWith(input, CONTINUE_SEARCH_CONTEXT_CMD_LONG) || CommandUtils::startsWith(input, CONTINUE_SEARCH_CONTEXT_CMD)) {
		newCommand = new ContinueSearchPhraseCommand();

	} else if (CommandUtils::startsWith(input, RETRIEVE_INPUT_PHRASE_CMD_LONG) || CommandUtils::startsWith(input, RETRIEVE_INPUT_PHRASE_CMD)) {
		newCommand = new CopyInputPhraseToWorkingPhraseCommand();

	} else if (CommandUtils::startsWith(input, REWARD_CMD_LONG) || CommandUtils::startsWith(input, REWARD_CMD2)) {
		newCommand = new RewardCommand();

	} else if (CommandUtils::startsWith(input, PARTIAL_REWARD_CMD_LONG) || CommandUtils::startsWith(input, PARTIAL_REWARD_CMD2)) {
		newCommand = new PartialRewardCommand();

	} else if (CommandUtils::startsWith(input, EXPLOIT_CMD_LONG) || CommandUtils::startsWith(input, EXPLOIT_CMD)) {
		newCommand = new ExploitCommand();

	} else if (CommandUtils::startsWith(input, CLEAN_EXPLOIT_CMD_LONG) || CommandUtils::startsWith(input, CLEAN_EXPLOIT_CMD)) {
		newCommand = new CleanExploitCommand();

	} else if (CommandUtils::startsWith(input, EXPLOIT_RANDOM_CMD_LONG) || CommandUtils::startsWith(input, EXPLOIT_RANDOM_CMD)) {
		newCommand = new ExploitRandomCommand();

	} else if (CommandUtils::startsWith(input, EXPLOIT_MEMORIZE_CMD_LONG) || CommandUtils::startsWith(input, EXPLOIT_MEMORIZE_CMD)) {
		newCommand = new ExploitMemorizeCommand();

	} else if (CommandUtils::startsWith(input, BEST_EXPLOIT_CMD_LONG) || CommandUtils::startsWith(input, BEST_EXPLOIT_CMD)) {
		newCommand = new BestExploitCommand();

	} else if (CommandUtils::startsWith(input, PUSH_GOAL_CMD_LONG) || CommandUtils::startsWith(input, PUSH_GOAL_CMD)) {
		newCommand = new PushGoalCommand();

	} else if (CommandUtils::startsWith(input, DROP_GOAL_CMD_LONG) || CommandUtils::startsWith(input, DROP_GOAL_CMD)) {
		newCommand = new DropGoalCommand();

	} else if (CommandUtils::startsWith(input, GET_GOAL_PHRASE_CMD_LONG) || CommandUtils::startsWith(input, GET_GOAL_PHRASE_CMD)) {
		newCommand = new GetGoalPhraseCommand();

	} else if (CommandUtils::startsWith(input,  WORKING_PHRASE_OUT_CMD_LONG) || CommandUtils::startsWith(input, WORKING_PHRASE_OUT_CMD)) {
		newCommand = new WorkingPhraseOutCommand();

	}
	else {
		newCommand = new Command();
	}

	newCommand->init(CommandFactory::annabell, CommandFactory::monitor, CommandFactory::aDisplay, CommandFactory::clk0,
			CommandFactory::clk1, input);

	return newCommand;
}
