#include "agents.h"
#include "fpmas/model/guards.h"
#include <sstream>

void log(
		fpmas::api::model::Model* model,
		std::string tag,
		fpmas::graph::DistributedId agent_id,
		std::string message) {
	std::cout << "-- Rank " << model->graph().getMpiCommunicator().getRank()
		<< " [" << model->runtime().currentDate() << "]["
		<< tag << agent_id << "] " << message << std::endl;
}

void log_read(
		fpmas::api::model::Model* model, int data,
		fpmas::api::graph::DistributedId reader,
		const fpmas::api::model::AgentNode* node) {
	std::ostringstream o_str;
	o_str << "Data read from " << node->state() << " DataAgent " << node->getId() <<": " << data;
	log(model, "RW_AGENT", reader, o_str.str());
}

void log_write(
		fpmas::api::model::Model* model, int data,
		fpmas::api::graph::DistributedId writer,
		fpmas::api::model::AgentNode* node) {
	std::ostringstream o_str;
	o_str << "Data written to " << node->state() << " DataAgent " << node->getId() << ": " << data;
	log(model, "RW_AGENT", writer, o_str.str());
}

void DataAgent::behavior() {
	fpmas::model::AcquireGuard acquire(this);
	this->data++;
	log(this->model(), "DATA", this->node()->getId(), "Updated data: " + std::to_string(data));

	// `acquire` goes out of scope, `this` is automatically released
}

void DataAgent::to_json(nlohmann::json& json, const DataAgent* agent) {
	json["data"] = agent->data;
	json["dw_count"] = agent->received_write_count;
}

DataAgent* DataAgent::from_json(const nlohmann::json& json) {
	return new DataAgent(json.at("data").get<int>(), json.at("dw_count").get<int>());
}

int ReaderWriterAgent::emitted_write_count = 0;

void ReaderWriterAgent::behavior() {
	for(auto data_agent : this->outNeighbors<const DataAgent>()) {
		fpmas::model::ReadGuard read(data_agent);
		log_read(
				this->model(), data_agent->data,
				this->node()->getId(), data_agent->node()
				);
	}
	for(auto data_agent : this->outNeighbors<DataAgent>()) {
		fpmas::model::AcquireGuard acquire(data_agent);
		data_agent->received_write_count++;
		ReaderWriterAgent::emitted_write_count++;

		log_write(
				this->model(), data_agent->received_write_count,
				this->node()->getId(), data_agent->node()
				);
	}
}
