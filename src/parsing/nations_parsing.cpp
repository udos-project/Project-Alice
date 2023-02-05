#include "system_state.hpp"
#include "nations.hpp"
#include "parsers_declarations.hpp"

namespace parsers {
void national_identity_file::any_value(std::string_view tag, association_type, std::string_view txt, error_handler& err, int32_t line, scenario_building_context& context) {
	if(tag.length() != 3) {
		err.accumulated_errors += err.file_name + " line " + std::to_string(line) + ": encountered a tag that was not three characters\n";
		return;
	}
	auto as_int = nations::tag_to_int(tag[0], tag[1], tag[2]);
	auto new_ident = context.state.world.create_national_identity();

	auto name_id = text::find_or_add_key(context.state, txt);
	auto adj_id = text::find_or_add_key(context.state, std::string(txt) + "_ADJ");
	context.state.world.national_identity_set_name(new_ident, name_id);
	context.state.world.national_identity_set_adjective(new_ident, adj_id);

	context.file_names_for_idents.resize(context.state.world.national_identity_size());
	context.file_names_for_idents[new_ident] = txt;
	context.map_of_ident_names.insert_or_assign(as_int, new_ident);

}

void triggered_modifier::finish(triggered_modifier_context& context) {
	auto name_id = text::find_or_add_key(context.outer_context.state, context.name);

	auto modifier_id = context.outer_context.state.world.create_modifier();

	context.outer_context.state.world.modifier_set_icon(modifier_id, uint8_t(icon_index));
	context.outer_context.state.world.modifier_set_name(modifier_id, name_id);
	this->convert_to_national_mod();
	context.outer_context.state.world.modifier_set_province_values(modifier_id, constructed_definition);

	context.outer_context.map_of_modifiers.insert_or_assign(std::string(context.name), modifier_id);

	context.outer_context.state.national_definitions.triggered_modifiers[context.index].linked_modifier = modifier_id;
}

void register_trigger(token_generator& gen, error_handler& err, triggered_modifier_context& context) {
	context.outer_context.set_of_triggered_modifiers.push_back(pending_triggered_modifier_content{gen, context.index});
}

void make_triggered_modifier(std::string_view name, token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto index = uint32_t(context.state.national_definitions.triggered_modifiers.size());
	context.state.national_definitions.triggered_modifiers.emplace_back();

	triggered_modifier_context new_context{context, index, name };
	parse_triggered_modifier(gen, err, new_context);
}

void make_national_value(std::string_view name, token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, name);

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string(name), new_modifier);
}

void m_very_easy_player(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "very_easy_player");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("very_easy_player"), new_modifier);
	context.state.national_definitions.very_easy_player = new_modifier;
}

void m_easy_player(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "easy_player");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("easy_player"), new_modifier);
	context.state.national_definitions.easy_player = new_modifier;
}

void m_hard_player(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "hard_player");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("hard_player"), new_modifier);
	context.state.national_definitions.hard_player = new_modifier;
}

void m_very_hard_player(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "very_hard_player");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("very_hard_player"), new_modifier);
	context.state.national_definitions.very_hard_player = new_modifier;
}

void m_very_easy_ai(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "very_easy_ai");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("very_easy_ai"), new_modifier);
	context.state.national_definitions.very_easy_ai = new_modifier;
}

void m_easy_ai(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "easy_ai");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("easy_ai"), new_modifier);
	context.state.national_definitions.easy_ai = new_modifier;
}

void m_hard_ai(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "hard_ai");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("hard_ai"), new_modifier);
	context.state.national_definitions.hard_ai = new_modifier;
}

void m_very_hard_ai(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "very_hard_ai");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("very_hard_ai"), new_modifier);
	context.state.national_definitions.very_hard_ai = new_modifier;
}

void m_overseas(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "overseas");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("overseas"), new_modifier);
	context.state.national_definitions.overseas = new_modifier;
}

void m_coastal(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "coastal");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("coastal"), new_modifier);
	context.state.national_definitions.coastal = new_modifier;
}

void m_non_coastal(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "non_coastal");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("non_coastal"), new_modifier);
	context.state.national_definitions.non_coastal = new_modifier;
}

void m_coastal_sea(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "coastal_sea");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("coastal_sea"), new_modifier);
	context.state.national_definitions.coastal_sea = new_modifier;
}

void m_sea_zone(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "sea_zone");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("sea_zone"), new_modifier);
	context.state.national_definitions.sea_zone = new_modifier;
}

void m_land_province(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "land_province");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("land_province"), new_modifier);
	context.state.national_definitions.land_province = new_modifier;
}

void m_blockaded(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "blockaded");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("blockaded"), new_modifier);
	context.state.national_definitions.blockaded = new_modifier;
}

void m_no_adjacent_controlled(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "no_adjacent_controlled");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("no_adjacent_controlled"), new_modifier);
	context.state.national_definitions.no_adjacent_controlled = new_modifier;
}

void m_core(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "core");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("core"), new_modifier);
	context.state.national_definitions.core = new_modifier;
}

void m_has_siege(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "has_siege");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("has_siege"), new_modifier);
	context.state.national_definitions.has_siege = new_modifier;
}

void m_occupied(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "occupied");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("occupied"), new_modifier);
	context.state.national_definitions.occupied = new_modifier;
}

void m_nationalism(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "nationalism");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("nationalism"), new_modifier);
	context.state.national_definitions.nationalism = new_modifier;
}

void m_infrastructure(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "infrastructure");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_province_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("infrastructure"), new_modifier);
	context.state.national_definitions.infrastructure = new_modifier;
}

void m_base_values(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "base_values");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("base_values"), new_modifier);
	context.state.national_definitions.base_values = new_modifier;
}

void m_war(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "war");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("war"), new_modifier);
	context.state.national_definitions.war = new_modifier;
}

void m_peace(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "peace");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("peace"), new_modifier);
	context.state.national_definitions.peace = new_modifier;
}

void m_disarming(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "disarming");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("disarming"), new_modifier);
	context.state.national_definitions.disarming = new_modifier;
}

void m_war_exhaustion(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "war_exhaustion");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("war_exhaustion"), new_modifier);
	context.state.national_definitions.war_exhaustion = new_modifier;
}

void m_badboy(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "badboy");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("badboy"), new_modifier);
	context.state.national_definitions.badboy = new_modifier;
}

void m_debt_default_to(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "debt_default_to");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("debt_default_to"), new_modifier);
	context.state.national_definitions.debt_default_to = new_modifier;
}

void m_bad_debter(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "bad_debter");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("bad_debter"), new_modifier);
	context.state.national_definitions.bad_debter = new_modifier;
}

void m_great_power(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "great_power");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("great_power"), new_modifier);
	context.state.national_definitions.great_power = new_modifier;
}

void m_second_power(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "second_power");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("second_power"), new_modifier);
	context.state.national_definitions.second_power = new_modifier;
}

void m_civ_nation(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "civ_nation");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("civ_nation"), new_modifier);
	context.state.national_definitions.civ_nation = new_modifier;
}

void m_unciv_nation(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "unciv_nation");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("unciv_nation"), new_modifier);
	context.state.national_definitions.unciv_nation = new_modifier;
}

void m_average_literacy(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "average_literacy");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("average_literacy"), new_modifier);
	context.state.national_definitions.average_literacy = new_modifier;
}

void m_plurality(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "plurality");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("plurality"), new_modifier);
	context.state.national_definitions.plurality = new_modifier;
}

void m_generalised_debt_default(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "generalised_debt_default");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("generalised_debt_default"), new_modifier);
	context.state.national_definitions.generalised_debt_default = new_modifier;
}

void m_total_occupation(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "total_occupation");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("total_occupation"), new_modifier);
	context.state.national_definitions.total_occupation = new_modifier;
}

void m_total_blockaded(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "total_blockaded");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("total_blockaded"), new_modifier);
	context.state.national_definitions.total_blockaded = new_modifier;
}

void m_in_bankrupcy(token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, "in_bankrupcy");

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	parsed_modifier.convert_to_national_mod();

	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);

	context.map_of_modifiers.insert_or_assign(std::string("in_bankrupcy"), new_modifier);
	context.state.national_definitions.in_bankrupcy = new_modifier;
}


void make_event_modifier(std::string_view name, token_generator& gen, error_handler& err, scenario_building_context& context) {
	auto name_id = text::find_or_add_key(context.state, name);

	auto parsed_modifier = parse_modifier_base(gen, err, context);
	
	auto new_modifier = context.state.world.create_modifier();

	context.state.world.modifier_set_icon(new_modifier, uint8_t(parsed_modifier.icon_index));
	context.state.world.modifier_set_name(new_modifier, name_id);

	parsed_modifier.convert_to_province_mod();
	context.state.world.modifier_set_province_values(new_modifier, parsed_modifier.constructed_definition);

	parsed_modifier.convert_to_neutral_mod();
	parsed_modifier.convert_to_national_mod();
	context.state.world.modifier_set_national_values(new_modifier, parsed_modifier.constructed_definition);
	
	context.map_of_modifiers.insert_or_assign(std::string(name), new_modifier);
}

void make_party(token_generator& gen, error_handler& err, country_file_context& context) {
	auto party_id = context.outer_context.state.world.create_political_party();
	if(!(context.outer_context.state.world.national_identity_get_political_party_first(context.id))) {
		context.outer_context.state.world.national_identity_set_political_party_first(context.id, party_id);
		context.outer_context.state.world.national_identity_set_political_party_count(context.id, uint8_t(1));
	} else {
		context.outer_context.state.world.national_identity_get_political_party_count(context.id) += uint8_t(1);
	}

	party_context new_context{ context.outer_context, party_id };
	parse_party(gen, err, new_context);
}

void make_unit_names_list(std::string_view name, token_generator& gen, error_handler& err, country_file_context& context) {
	if(auto it = context.outer_context.map_of_unit_types.find(std::string(name)); it != context.outer_context.map_of_unit_types.end()) {
		auto found_type = it->second;
		unit_names_context new_context{ context.outer_context, context.id, found_type };
		parse_unit_names_list(gen, err, new_context);
	} else {
		err.accumulated_errors += "No unit type named " + std::string(name) + " (" + err.file_name + ")\n";
		gen.discard_group();
	}

	
}

}
