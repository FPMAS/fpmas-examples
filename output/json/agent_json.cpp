#include "fpmas.h"
#include "agent.h"

FPMAS_JSON_SET_UP(Agent);

using fpmas::api::utils::PtrWrapper;

FPMAS_DEFINE_GROUPS(GROUP_0);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent)
	fpmas::init(argc, argv);
	{
		// Model initialization
		fpmas::model::Model<fpmas::synchro::GhostMode> model;
		fpmas::model::Behavior<Agent> agent_behavior(&Agent::generate_new_message);
		auto& group = model.buildGroup(GROUP_0, agent_behavior);
		for(int i = 0; i < 2; i++)
			group.add(new Agent);

		// Opens a distinct file on each process
		fpmas::io::DynamicFileOutput file(
				"agent.%r.%t.json",
				model.getMpiCommunicator(),
				model.runtime()
				);
		// JsonOutput definition
		fpmas::io::JsonOutput<std::vector<PtrWrapper<fpmas::api::model::Agent>>> output(
				// dynamic output stream
				file,
				// Lambda function based Watcher: fetches LOCAL agents in the
				// group
				[&group] () {
					// Utility functions to easily cast
					// std::vector<fpmas::api::model::Agent*> to
					// std::vector<PtrWrapper<fpmas::api::model::Agent>> to enable
					// nlohmann json serialization
					return fpmas::utils::ptr_wrapper_cast<fpmas::api::model::Agent>(
							group.localAgents()
							);
				},
				true // Automatically indents JSON output
				);

		// Behavior execution
		model.scheduler().schedule(0, 1, group.jobs());
		// Json output
		model.scheduler().schedule(0.1, 1, output.job());

		// Runs 2 time steps of the model
		model.runtime().run(2);
	}
	fpmas::finalize();
}
