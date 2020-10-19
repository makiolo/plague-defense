#include "TreeNodeComposite.h"
// 
#include "myBT.h"

namespace myBT {

void TreeNodeComposite::unserialize(nlohmann::json& pipe, const ConditionRepository& conditions, const ActionRepository& actions)
{
	this->read(pipe);
	for (auto& child : pipe["childs"])
	{
		std::string type = child["type"].get<std::string>();
		std::string name = child["name"].get<std::string>();
		// Please, need factory :D
		if (type == "Sequence")
		{
			auto newchild = this->make_node<Sequence>(name);
			newchild->unserialize(child, conditions, actions);
		}
        else if (type == "Parallel")
        {
            auto newchild = this->make_node<Parallel>(name);
            newchild->unserialize(child, conditions, actions);
        }
		else if (type == "Selector")
		{
			auto newchild = this->make_node<Selector>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Assert")
		{
			auto newchild = this->make_node<Assert>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "While")
		{
			auto newchild = this->make_node<While>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "For")
		{
			auto newchild = this->make_node<For>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Fortime")
		{
			auto newchild = this->make_node<ForTime>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "And")
		{
			auto newchild = this->make_node<And>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Or")
		{
			auto newchild = this->make_node<Or>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Condition")
		{
			auto newchild = this->make_node<Condition>(name, conditions.at(name));
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Action")
		{
			auto newchild = this->make_node<Action>(name, actions.at(name));
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Aborted")
		{
			auto newchild = this->make_node<Aborted>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Completed")
		{
			auto newchild = this->make_node<Completed>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Failed")
		{
			auto newchild = this->make_node<Failed>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "Running")
		{
			auto newchild = this->make_node<Running>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "True")
		{
			auto newchild = this->make_node<AlwaysFalse>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else if (type == "False")
		{
			auto newchild = this->make_node<AlwaysTrue>(name);
			newchild->unserialize(child, conditions, actions);
		}
		else
		{
			std::abort();
		}
	}
}

void TreeNodeComposite::write_ai(const std::string& filename, const ConditionRepository& conditions, const ActionRepository& actions)
{
	nlohmann::json pipe;

	std::vector<std::string> available_conditions;
	for (ConditionRepository::const_iterator iter = conditions.begin(); iter != conditions.end(); ++iter)
	{
		std::string key = iter->first;
		available_conditions.push_back(key);
	}

	std::vector<std::string> available_actions;
	for (ActionRepository::const_iterator iter = actions.begin(); iter != actions.end(); ++iter)
	{
		std::string key = iter->first;
		available_actions.push_back(key);
	}

	pipe["available_conditions"] = available_conditions;
	pipe["available_actions"] = available_actions;

	this->serialize(pipe);

	std::ofstream myfile;
	myfile.open(filename);
	// pretyprint
	myfile << std::setw(4) << pipe.dump(4) << std::endl;
	// fastprint
    // myfile << pipe.dump() << std::endl;
	myfile.close();
}

void TreeNodeComposite::read_ai(const std::string& filename, const ConditionRepository& conditions, const ActionRepository& actions)
{
	std::ifstream myfile(filename);
	nlohmann::json pipe;
	myfile >> pipe;

	std::vector<std::string> available_conditions;
	for (ConditionRepository::const_iterator iter = conditions.begin(); iter != conditions.end(); ++iter)
	{
		std::string key = iter->first;
		available_conditions.push_back(key);
	}

	std::vector<std::string> available_actions;
	for (ActionRepository::const_iterator iter = actions.begin(); iter != actions.end(); ++iter)
	{
		std::string key = iter->first;
		available_actions.push_back(key);
	}

	auto available_conditions_json = pipe["available_conditions"].get<std::vector<std::string>>();
	auto available_actions_json = pipe["available_actions"].get<std::vector<std::string>>();

	assert(available_conditions == available_conditions_json);
	assert(available_actions == available_actions_json);

	this->unserialize(pipe, conditions, actions);
}

}
