#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

#define AGENT_TYPES DataAgent, ReaderWriterAgent

struct ReaderWriterBehavior {
	virtual void behavior() = 0;
};

class DataAgent :
	public fpmas::model::AgentBase<DataAgent>,
	public ReaderWriterBehavior {
	public:
		/**
		 * Self managed data, read by ReaderWriterAgents.
		 */
		int data;
		/**
		 * Integer on which ReaderWriterAgents are writting.
		 */
		int received_write_count;

		DataAgent() = default;
		DataAgent(int data, int received_write_count)
			: data(data), received_write_count(received_write_count) {}

		/**
		 * Increases data by 1.
		 */
		void behavior() override;

		static void to_json(nlohmann::json& json, const DataAgent* agent);
		static DataAgent* from_json(const nlohmann::json& json);
};

class ReaderWriterAgent :
	public fpmas::model::AgentBase<ReaderWriterAgent>,
	public ReaderWriterBehavior {
	public:
		/**
		 * Static integer to count write operations performed by all
		 * ReaderWriterAgents on this process.
		 */
		static int emitted_write_count;

		/**
		 * Read data from DataAgents, and increases each connected DataAgent's
		 * received_write_count by 1.
		 */
		void behavior() override;
};

FPMAS_DEFAULT_JSON(ReaderWriterAgent)
